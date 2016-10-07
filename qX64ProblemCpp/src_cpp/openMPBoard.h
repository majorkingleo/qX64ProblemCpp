/*
 * openMPBoard.h
 *
 *  Created on: 06.10.2016
 *      Author: martin
 */

#ifndef OPENMPBOARD_H_
#define OPENMPBOARD_H_

#include "board.h"

class OpenMPBoard : public Board
{
public:
	OpenMPBoard( const unsigned int size, bool allow_null_rows_ = false )
	: Board( size,  allow_null_rows_ )
	{}

	virtual bool verify();
};

#endif /* OPENMPBOARD_H_ */
