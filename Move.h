/*
 * Move.h
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#ifndef MOVE_H_
#define MOVE_H_

struct Move final {
	explicit Move(int x, int y);
	int x;
	int y;
};

#endif /* MOVE_H_ */
