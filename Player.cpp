/*
 * Player.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include "Player.h"

Player::Player(bool playerX)
{
	player = playerX ? ttt::Player::XPlayer : ttt::Player::OPlayer;
}

Player::~Player() {}
