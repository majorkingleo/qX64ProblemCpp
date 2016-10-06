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
	bool print_all;

public:
	Engine( unsigned int size, bool print_all );

	void run() {
		gen_next_board();
	}
protected:

	void gen_next_board();

	void print_board( std::vector<Queen> & queens );
	void print_board( Board & board );
};


#endif /* ENGINE_H_ */
