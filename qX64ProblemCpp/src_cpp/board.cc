/*
 * board.cc
 *
 *  Created on: 29.09.2016
 *      Author: martin
 */

#include "board.h"
#include <cpp_util.h>
#include <debug.h>

using namespace Tools;

Board::Board( const Board & other )
: SIZE( other.SIZE ),
  MAX_SIZE(max_size()),
  allow_null_rows(other.allow_null_rows),
  board(0)
{
	board = new ROW_TYPE[SIZE];

	for( unsigned i = 0; i < SIZE; i++ )
	{
		board[i] = other.board[i];
	}
}

Board & Board::operator=( const Board & other )
{
	if( SIZE != other.SIZE ) {
		throw REPORT_EXCEPTION( "invalid assignment");
	}

	if( allow_null_rows != other.allow_null_rows ) {
		throw REPORT_EXCEPTION( "invalid assignment");
	}

	clear();

	board = new ROW_TYPE[SIZE];

	for( unsigned i = 0; i < SIZE; i++ )
	{
		board[i] = other.board[i];
	}

	return *this;
}

void Board::create()
{
	if( SIZE > max_size() )
	{
		throw REPORT_EXCEPTION( format( "SIZE %s > max board size of %d", SIZE, max_size() ));
	}

	board = new ROW_TYPE[SIZE];

	reset();
}

void Board::create_if_not_exists()
{
	if( !board ) {
		create();
	}
}

std::string Board::Row2String( ROW_TYPE row, bool even )
{
	std::stringstream str;

	ROW_TYPE mask = 1;

	unsigned int shift_count = 0;

	for( mask <<= MAX_SIZE -1; mask > 0 && shift_count < SIZE; mask >>= 1, shift_count++ )
	{
		if( row & mask ) {
			str << 'Q';
		} else {
			if( even ) {
				str << '_';
			} else {
				str << '#';
			}
		}

		even = !even;
	}

	return str.str();
}

std::string Board::toString()
{
	create_if_not_exists();

	std::stringstream str;

	// printer header

	str << "Board: " << SIZE << " allow_null_rows: " << x2s(allow_null_rows) << '\n';

	str << "  ";

	char letter = 'A';

	for( int i = SIZE-1, j = 0; i >= 0; i--, j++ )
	{
		str << (char)(letter+j);
	}

	str << '\n';

	// print board

	for( int i = SIZE-1; i >= 0; i-- )
	{
		str << i+1 << ' ' << Row2String( board[i], i % 2 ) << '\n';
	}

	return str.str();
}

unsigned long Board::max_size()
{
	return sizeof(ROW_TYPE)*8;
}

void Board::clear()
{
	delete[] board;
	board=0;
}

void Board::reset()
{
	for( unsigned i = 0; i < SIZE; i++ )
	{
		board[i] = 0;
	}
}

void Board::set_queen( unsigned col, unsigned row )
{
	create_if_not_exists();

	if( row < 1 ) {
		throw REPORT_EXCEPTION( format( "invalid row %d", row));
	}

	if( row > SIZE ) {
		throw REPORT_EXCEPTION( format( "invalid row %d max SIZE %d", row, SIZE));
	}

	ROW_TYPE & board_row = board[row-1];

	ROW_TYPE mask = 1;
	mask <<= MAX_SIZE - col;

	// std::cout << Row2String( mask, true ) << std::endl;

	board_row |= mask;
}

bool Board::verify()
{
	ROW_TYPE mask_start = 1;
	mask_start <<= MAX_SIZE -1;

	short queens_by_col[SIZE];

	for( unsigned i = 0; i < SIZE; i++ ) {
		queens_by_col[i] = 0;
	}

	ROW_TYPE queens_masks_by_row[SIZE];

	for( unsigned i = 0; i < SIZE; i++ ) {
		queens_masks_by_row[i] = 0;
	}

	// one quen by row verification
	for( int i = SIZE-1; i >= 0; i-- )
	{
		if( board[i] == 0 ) {

			if( allow_null_rows )
			{
				continue;
			}
			else
			{
				return false;
			}
		}

		bool valid_mask_found = false;

		ROW_TYPE mask = 1;
		unsigned int shift_count = 0;

		for( mask = mask_start; mask > 0 && shift_count < SIZE; mask >>= 1, shift_count++ )
		{
			DEBUG( format("i: %d shift_count: %d mask: %s", i, shift_count, Row2String(mask,false)) );

			if( board[i] & mask )
			{
				valid_mask_found = true;

				queens_masks_by_row[i] = mask;

				queens_by_col[shift_count]++;

				// col verification, more than one queen per col is invalid
				if ( queens_by_col[shift_count] > 1 )
				{
					return false;
				}

				break;
			}
		}

		if( !valid_mask_found ) {
			return false;
		}
	}

	for( int i = SIZE-1; i >= 0; i-- )
	{
		ROW_TYPE mask = queens_masks_by_row[i];

		for( int j = SIZE-1; j >= 0; j-- )
		{
			if( i == j ) {
				continue;
			}

			ROW_TYPE tmp = mask;
			tmp <<= i - j;

			DEBUG( format( "i: %d j: %d mask %s tmp: %s board[j]: %s",
					i, j,
					Row2String(mask,false),
					Row2String(tmp,false),
					Row2String(board[j], false)) );

			if( board[j] & tmp )
			{
				DEBUG( "diagonal match" );
				return false;
			}

			tmp = mask;
			tmp >>= i - j;

			if( board[j] & tmp )
			{
				DEBUG( "diagonal match" );
				return false;
			}
		}
	}

	return true;
}
