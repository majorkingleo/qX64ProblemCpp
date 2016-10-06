/*
 * board.h
 *
 *  Created on: 29.09.2016
 *      Author: martin
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <string>

class Queen
{
public:
	unsigned row;
	char     col;

	Queen *next_queen;

	Queen( unsigned row_ = 1, char col_ = 'A' )
	: row( row_ ),
	  col( col_ ),
	  next_queen(0)
	{}

	void set_next_queen( Queen *next )
	{
		next_queen = next;
	}

	/*
	 * return true if end is reached
	 */
	bool inc_row( const unsigned SIZE )
	{
		row++;
		if( row > SIZE )
		{
			row = 1;
			if( next_queen )
			{
				return next_queen->inc_row( SIZE );
			} else {
				return true;
			}
		}
		return false;
	}
};


class Board
{
public:

	typedef unsigned long ROW_TYPE;

	const unsigned int SIZE;
	const unsigned int MAX_SIZE;
	const bool allow_null_rows;

protected:

	ROW_TYPE *board;

public:
	Board( const unsigned int size, bool allow_null_rows_ = false )
	: SIZE( size ),
	  MAX_SIZE(max_size()),
	  allow_null_rows(allow_null_rows_),
	  board(0)
	{}

	Board( const Board & other );

	Board & operator=( const Board & other );

	virtual ~Board()
	{
		clear();
	}

	void clear();
	void create();
	void create_if_not_exists();

	std::string toString();

	std::string Row2String( ROW_TYPE row, bool even = false );

	static unsigned long max_size();

	void reset();

	void set_queen( unsigned col, unsigned row );

	void set_queen( char col, unsigned row )
	{
		set_queen(  (unsigned)(col - 'A' + 1), row );
	}

	void set_queen( const Queen & queen )
	{
		set_queen( queen.col, queen.row );
	}

	virtual bool verify();

	unsigned int get_size() const {
		return SIZE;
	}

	bool get_allow_null_rows() const {
		return allow_null_rows;
	}

	const ROW_TYPE *get_board() const {
		return board;
	}

	void set_board( ROW_TYPE *b ) {
		clear();
		board = b;
	}
};


#endif /* BOARD_H_ */
