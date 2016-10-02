/*
 * main.cc
 *
 *  Created on: 29.09.2016
 *      Author: martin
 */


#include <arg.h>
#include "board.h"
#include <iostream>
#include <arg.h>
#include <format.h>
#include <OutDebug.h>
#include <cpp_util.h>
#include "Engine.h"
#include "writeBoard.h"

using namespace Tools;

void usage( const std::string & prog )
{

}

int main( int argc, char **argv )
{
	Arg::Arg arg( argc, argv );
	unsigned int console_width = 80;

	arg.addPrefix( "-" );
	arg.addPrefix( "--" );

	arg.setMinMatch(1);

	Arg::OptionChain oc_info;
	arg.addChainR( &oc_info );
	oc_info.setMinMatch( 1 );
	oc_info.setContinueOnMatch( false );
	oc_info.setContinueOnFail( true );

	Arg::FlagOption o_help( "h" );
	o_help.addName( "help" );
	o_help.setDescription( "Show this page" );
	oc_info.addOptionR( &o_help );

	Arg::FlagOption o_version( "v" );
	o_version.addName( "version" );
	o_version.setDescription( "Show replace version number" );
	oc_info.addOptionR( &o_version );


	Arg::FlagOption o_debug("d");
	o_debug.addName( "debug" );
	o_debug.setDescription("print debugging messages");
	o_debug.setRequired(false);
	arg.addOptionR( &o_debug );


	Arg::IntOption o_size("size");
	o_size.setDescription(format("board size (default is 8, min is 1 max is %d)", Board::max_size() ));
	o_size.setRequired(false);
	arg.addOptionR( &o_size );

	try {

		unsigned int BOARD_SIZE = 8;

		if( !arg.parse() )
		{
			if( o_version.getState() )
			{
				std::cout << format("%s version %s\n", argv[0], VERSION);
				return 0;
			} else {
				usage(argv[0]);
				std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
				return 1;
			}
		}

		if( o_help.getState() )
		{
			usage(argv[0]);
			std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
			return 0;
		}

		if( o_debug.getState() )
		{
			Tools::x_debug = new OutDebug();
		}

		if( o_size.isSet() )
		{
			BOARD_SIZE = s2x<int>(o_size.getValues()->at(0),8);

			if( BOARD_SIZE < 1 || BOARD_SIZE > Board::max_size() )
			{
				throw REPORT_EXCEPTION( format( "invalid board size %d",BOARD_SIZE ) ) ;
				usage(argv[0]);
				std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
				return 1;
			}
		}

/*
		Board board(BOARD_SIZE);


		board.set_queen( 'A', 1 );
		board.set_queen( 'B', 2 );
		board.set_queen( 'C', 3 );
		board.set_queen( 'D', 4 );
		board.set_queen( 'E', 5 );
		board.set_queen( 'F', 6 );
		board.set_queen( 'G', 7 );
		board.set_queen( 'H', 8 );


		board.set_queen( 'A', 3 );
		board.set_queen( 'F', 5 );

		std::cout << board.toString() << std::endl;


		std::cout << "verify: " << board.verify() << std::endl;


		WriteBoard write_board( "test.bin" );

		if( !write_board ) {
			throw REPORT_EXCEPTION( "cannot open file" );
		}

		write_board.write( board );
*/

		/*
		ReadBoard read_board( "test.bin");

		if( !read_board ) {
			throw REPORT_EXCEPTION( "cannot open file" );
		}

		Board *board = read_board.read_next();

		std::cout << board->toString() << std::endl;

		delete board;
*/

		ReadBoardText read_board( "text.txt");

		if( !read_board ) {
			throw REPORT_EXCEPTION( "cannot open file" );
		}

		Board *board = read_board.read_next();

		std::cout << board->toString() << std::endl;

		delete board;

		/*
		Engine engine(BOARD_SIZE);
		engine.run();
		 */
	} catch( std::exception & err ) {
		std::cerr << "Error: " << err.what() << std::endl;
		usage(argv[0]);
		std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
		return 1;
	}
}
