/*
 * Move.h
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#ifndef MOVE_H_
#define MOVE_H_

#include <iosfwd>

struct Move final {
	explicit Move(int x, int y);
	int x;
	int y;
	std::ostream& print(std::ostream& stream) const;
};

bool operator==(const Move& lhs, const Move& rhs);
bool operator!=(const Move& lhs, const Move& rhs);
std::ostream& operator<< (std::ostream& stream, const Move& move);

#endif /* MOVE_H_ */
