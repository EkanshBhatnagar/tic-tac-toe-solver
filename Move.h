/*
 * Move.h
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#ifndef MOVE_H_
#define MOVE_H_

#include <iosfwd>
#include <cstdint>

struct Move final {
	explicit Move(uint8_t x, uint8_t y);
	uint8_t x;
	uint8_t y;
	std::ostream& print(std::ostream& stream) const;
	Move& operator=(const Move& rhs);
};

bool operator==(const Move& lhs, const Move& rhs);
bool operator!=(const Move& lhs, const Move& rhs);
std::ostream& operator<<(std::ostream& stream, const Move& move);

#endif /* MOVE_H_ */
