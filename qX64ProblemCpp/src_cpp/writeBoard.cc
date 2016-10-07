/*
 * writeBoard.cc
 *
 *  Created on: 01.10.2016
 *      Author: martin
 */

#include "writeBoard.h"
#include <string_utils.h>
#include <cpp_util.h>

using namespace Tools;

WriteBoard::WriteBoard( const std::string & file )
: out( file.c_str() ,std::ios_base::binary | std::ios_base::out | std::ios_base::trunc )
{

}

void WriteBoard::write( const Board & board )
{
	unsigned int size = board.get_size();
	bool allow_null_rows = board.get_allow_null_rows();

	out.write((char*)&size,sizeof(size));
	out.write((char*)&allow_null_rows,sizeof(allow_null_rows));

	const Board::ROW_TYPE *b = board.get_board();

	out.write( (const char*)b, sizeof(Board::ROW_TYPE) * board.get_size() );
}

ReadBoard::ReadBoard( const std::string & file )
: in( file.c_str() ,std::ios_base::binary | std::ios_base::in )
{

}

Board* ReadBoard::read_next()
{
	unsigned int size = 0;
	bool allow_null_rows = false;

	if( in.eof() ) {
		return 0;
	}

	in.read( (char*)&size, sizeof(size));
	in.read( (char*)&allow_null_rows, sizeof(allow_null_rows));

	if( size > Board::MAX_SIZE ) {
		throw REPORT_EXCEPTION( format( "size of board %d bigger than maximum board size of %d", size, Board::MAX_SIZE ));
	}

	if( size < 2 ) {
		throw REPORT_EXCEPTION( "minimal board size is 2" );
	}

	Board::ROW_TYPE *b = new Board::ROW_TYPE[size];

	in.read((char*)b,sizeof(Board::ROW_TYPE) * size);

	Board *board = new Board( size, allow_null_rows );
	board->set_board( b );

	return board;
}


ReadBoardText::ReadBoardText( const std::string & file )
: in( file.c_str() )
{

}

Board* ReadBoardText::read_next()
{
	std::string ss;

	do {

		if( in.eof() ) {
			return 0;
		}

		getline( in, ss );

		ss = strip(ss);

	} while( ss.empty() );


	std::vector<std::string> sl = split_simple( ss, " \t" );

	if( sl.size() != 4 )
	{
		throw REPORT_EXCEPTION( format( "%s invalid header in ASCII format: '%s' splitted size is %d",
				ss, sl.size()) );
	}

	unsigned int size = s2x<unsigned int>(sl[1],0);

	if( size > Board::MAX_SIZE ) {
		throw REPORT_EXCEPTION( format( "size of board %d bigger than maximum board size of %d", size, Board::MAX_SIZE ));
	}

	if( size < 2 ) {
		throw REPORT_EXCEPTION( "minimal board size is 2" );
	}

	bool allow_null_rows = s2bool(sl[3]);

	getline( in, ss ); // header

	Board *board = new Board( size, allow_null_rows );

	for( int i = size, line=2; i > 0; i--, line++ )
	{
		getline( in, ss );

		std::string::size_type pos = ss.find( ' ' );

		if( pos == std::string::npos )
		{
			throw REPORT_EXCEPTION( format( "cannot parse board at line %d line: '%s'", line, ss ));
		}

		std::string l = ss.substr(pos+1);

		if( l.size() != size )
		{
			throw REPORT_EXCEPTION( format(  "cannot parse board at line %d line: %s line size is %d expected %d",
					line, ss, l.size(), size ));
		}

		for( unsigned j = 0; j < l.size() && j < size; j++ )
		{
			if( l[j] == 'Q' )
			{
				Queen queen(i,'A'+j);
				board->set_queen(queen);
			}
		}
	}

	return board;
}

