/*
 * Move.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <assert.h>
#include <ostream>
#include "Move.h"
using namespace std;

Move::Move(int x, int y) : x{x}, y{y}
{
	assert(x >= 0 && x <= 2 && y >= 0 && y <= 2);
}

bool operator==(const Move& lhs, const Move& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Move& lhs, const Move& rhs)
{
	return !(lhs == rhs);
}

ostream& Move::print(ostream& stream) const
{
	return stream << "Move{" << x << "," << y << "}";
}

ostream& operator<< (ostream& stream, const Move& move)
{
	return move.print(stream);
}
