/*
 * OpenMPEngine.h
 *
 *  Created on: 06.10.2016
 *      Author: martin
 */

#ifndef OPENMPENGINE_H_
#define OPENMPENGINE_H_

#include "Engine.h"

class OpenMPEngine : public Engine
{

public:
	OpenMPEngine( unsigned int size_, bool print_all_ )
	: Engine( size_, print_all_ )
	{}


protected:

	virtual void gen_next_board();
};


#endif /* OPENMPENGINE_H_ */
