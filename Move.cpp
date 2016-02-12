/*
 * Move.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <assert.h>
#include "Move.h"

Move::Move(int x, int y, bool playerX) : x{x}, y{y}, playerX{playerX}
{
	assert(x > 0 && x <= 2 && y > 0 && y <= 2);
}

Move::~Move() {
	// TODO Auto-generated destructor stub
}

