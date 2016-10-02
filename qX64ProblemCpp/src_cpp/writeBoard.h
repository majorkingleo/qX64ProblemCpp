/*
 * writeBoard.h
 *
 *  Created on: 01.10.2016
 *      Author: martin
 */

#ifndef WRITEBOARD_H_
#define WRITEBOARD_H_

#include <iostream>
#include <fstream>
#include <string>
#include <board.h>

class WriteBoard
{
	std::ofstream out;

public:
	WriteBoard( const std::string & file );

	bool operator!() {
		return !out;
	}

	void write( const Board & board );
};


class ReadBoard
{
	std::ifstream in;

public:
	ReadBoard( const std::string & file );

	bool operator!() {
		return !in;
	}

	Board* read_next();
};

class ReadBoardText
{
	std::ifstream in;

public:
	ReadBoardText( const std::string & file );

	bool operator!() {
		return !in;
	}

	Board* read_next();
};


#endif /* WRITEBOARD_H_ */
