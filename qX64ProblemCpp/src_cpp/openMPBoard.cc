/*
 * openMPBoard.cc
 *
 *  Created on: 06.10.2016
 *      Author: martin
 */

#ifndef OPENMPBOARD_CC_
#define OPENMPBOARD_CC_

#include "openMPBoard.h"
#include <debug.h>
#include <format.h>
#include <omp.h>
#include <string.h>

using namespace Tools;

bool OpenMPBoard::verify()
{
	create_if_not_exists();

	ROW_TYPE mask_start = 1;
	mask_start <<= MAX_SIZE -1;

	short queens_by_col[SIZE];
	memset(&queens_by_col, 0, sizeof(queens_by_col));

	ROW_TYPE queens_masks_by_row[SIZE];
	memset(&queens_masks_by_row, 0, sizeof(queens_masks_by_row));

	// one quen by row verification

	bool invalid = false;

	//#pragma omp for
	for( int i = SIZE-1; i >= 0; i-- )
	{
		if( board[i] == 0 ) {

			if( allow_null_rows )
			{
				continue;
			}
			else
			{
				invalid = true;
			}
		}
	}

	if( invalid ) {
		return false;
	}

	invalid = false;

	#pragma omp for
	for( int i = SIZE-1; i >= 0; i-- )
	{
		bool valid_mask_found = false;

		ROW_TYPE mask = 1;
		unsigned int shift_count = 0;

		for( mask = mask_start; mask > 0 && shift_count < SIZE; mask >>= 1, shift_count++ )
		{
			DEBUG( format("i: %d shift_count: %d mask: %s", i, shift_count, Row2String(mask)) );

			if( (board[i] & mask) == board[i])
			{
				DEBUG( format( "Board: %s matches mask %s",  Row2String(board[i]),  Row2String(mask)))

				valid_mask_found = true;

				queens_masks_by_row[i] = mask;

				queens_by_col[shift_count]++;

				// col verification, more than one queen per col is invalid
				if ( queens_by_col[shift_count] > 1 )
				{
					invalid = true;
				}

				break;
			}
		}

		if( !valid_mask_found ) {
			invalid = true;
		}
	}

	if( invalid ) {
		return false;
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

#endif /* OPENMPBOARD_CC_ */
