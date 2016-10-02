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

class ReadBoardBase
{
public:
	virtual ~ReadBoardBase() {}

	virtual bool operator!() const = 0;

	virtual Board* read_next() = 0;

	bool valid() const {
		return !operator!();
	}
};

class ReadBoard : public ReadBoardBase
{
	std::ifstream in;

public:
	ReadBoard( const std::string & file );

	virtual bool operator!() const {
		return !in;
	}

	virtual Board* read_next();
};

class ReadBoardText : public ReadBoardBase
{
	std::ifstream in;

public:
	ReadBoardText( const std::string & file );

	virtual bool operator!() const {
		return !in;
	}

	virtual Board* read_next();
};


#endif /* WRITEBOARD_H_ */
