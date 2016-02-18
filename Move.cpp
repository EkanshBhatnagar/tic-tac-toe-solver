/*
 * Move.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <assert.h>
#include "Move.h"

Move::Move(int x, int y) : x{x}, y{y}
{
	assert(x >= 0 && x <= 2 && y >= 0 && y <= 2);
}
