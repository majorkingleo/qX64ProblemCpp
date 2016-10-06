/*
 * Engine.cc
 *
 *  Created on: 30.09.2016
 *      Author: martin
 */

#include "Engine.h"
#include <iostream>
#include <format.h>

using namespace Tools;

Engine::Engine( unsigned int size, bool print_all_ )
: SIZE( size ),
  print_all( print_all_ )
{

}

void Engine::print_board( std::vector<Queen> & queens )
{
	Board board(SIZE,false);

	for( unsigned q = 0; q < queens.size(); q++ )
	{
		board.set_queen( queens[q] );
	}

	print_board( board );
}

void Engine::print_board( Board & board )
{
	std::cout << board.toString() << "\n valid: " << x2s( board.verify() ) << "\n\n";
}

void Engine::gen_next_board()
{
	std::vector<Queen> queens(SIZE);

	char col = 'A';

	for( unsigned i = 0; i < SIZE; i++, col++ )
	{
		queens[i].row = 1;
		queens[i].col = col;

		if( i < SIZE-1 )
		{
			queens[i].set_next_queen( &queens[i+1] );
		}
	}

	// std::cout << board.toString() << "Status: " << ( board.verify() ? "Ok" : "false" ) << std::endl;

	int count = 0;

	int count_valid = 0;

	while( queens[SIZE-1].row <= SIZE )
	{
		Board board(SIZE,false);

		for( unsigned q = 0; q < queens.size(); q++ )
		{
			board.set_queen( queens[q] );
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

		count++;
		if( queens[0].inc_row( SIZE ) ) {
			break;
		}
	}

	std::cout << format("possible positions: %d valid positions: %d\n", count, count_valid );
}


