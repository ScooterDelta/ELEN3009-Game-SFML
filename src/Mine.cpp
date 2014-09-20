#include "Mine.h"

Mine::Mine(Vector2f position, Players::PLAYER player):
	_position{position},
	_isActive{false},
	_player{player}
{}

// Return the direction the object is facing.
float Mine::getDirection()
{
	return _direction.getAngle();
}

// Return the position of the object.
Vector2f Mine::getPosition()
{
	return _position;
}

// Return the size of the object
RectSize Mine::getSize()
{
	return _size;
}

bool Mine::checkIsActive()
{
	return _isActive;
}

void Mine::activateMine()
{
	if(_isActive == false)
		_isActive = true;
}


Players::PLAYER Mine::getPlayer()
{
	return _player;
}
