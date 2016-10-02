/*
 * Engine.h
 *
 *  Created on: 30.09.2016
 *      Author: martin
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <board.h>

class Engine
{
	const unsigned int SIZE;

public:
	Engine( unsigned int size );

	void run() {
		gen_next_board();
	}
protected:

	void gen_next_board();

	void print_board( std::vector<Queen> & queens );
};


#endif /* ENGINE_H_ */
