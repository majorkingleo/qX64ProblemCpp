/*
 * OpenMPEngine.cc
 *
 *  Created on: 06.10.2016
 *      Author: martin
 */

#include "OpenMPEngine.h"
#include <iostream>
#include <format.h>
#include <omp.h>
#include <math.h>
#include <list>
#include "debug.h"

using namespace Tools;

void OpenMPEngine::gen_next_board()
{
	std::vector<Queen> queens(SIZE);

	char col = 'A';

	#pragma omp for
	for( unsigned i = 0; i < SIZE; i++)
	{
		queens[i].row = 1;
		queens[i].col = col;

		if( i < SIZE-1 )
		{
			queens[i].set_next_queen( &queens[i+1] );
		}
		col++;
	}

	// std::cout << board.toString() << "Status: " << ( board.verify() ? "Ok" : "false" ) << std::endl;

	int count = 0;

	int count_valid = 0;

	long max = powl(SIZE,SIZE);

	const unsigned int BLOCKSIZE = SIZE*1000;

	std::vector<Board> boards(BLOCKSIZE);

	std::list<Board> solution_boards;

	#pragma omp for
	for( unsigned i = 0; i < boards.size(); i++ )
	{
		boards[i] = Board( SIZE, false );
		boards[i].create();
	}

	// #pragma omp parallel for lastprivate(count)
	for(  count = 0; count < max; count += BLOCKSIZE )
	{
		DEBUG( format( "count: %d", count ));

		for( unsigned i = 0; i < BLOCKSIZE; i++ )
		{
			boards[i].reset();
		}

		for( unsigned i = 0; i < BLOCKSIZE; i++ )
		{
			for( unsigned q = 0; q < queens.size(); q++ )
			{
				boards[i].set_queen_fast( queens[q] );
			}

			if( queens[0].inc_row( SIZE ) ) {
				break;
			}
		}

		for( unsigned i = 0; i < BLOCKSIZE; i++ )
		{
			if( boards[i].verify() )
			{
				solution_boards.push_back( boards[i] );
			}
		}
	}


#if 0
	//#pragma omp parallel for lastprivate(count), shared(count_valid)
	for( count = 0; count < max; count++ )
	{
		Board board(SIZE,false);
		board.create();

		for( unsigned q = 0; q < queens.size(); q++ )
				{
					board.set_queen_fast( queens[q] );
				}

		if( board.verify() )
		{
			count_valid++;
			print_board( board );
		}
		else if( print_all )
		{
			print_board( board );
		}

		queens[0].inc_row( SIZE );
	}
#endif

	std::cout << format("possible positions: %d valid positions: %d\n", count, solution_boards.size() );
}
