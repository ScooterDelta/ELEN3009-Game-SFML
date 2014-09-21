#ifndef MISSILE_H_
#define MISSILE_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Angle.h"
#include "DrawableObject.h"
#include "Score.h"

using namespace sf;

class Missile : public DrawableObject
{
public:
	// Constructor
	Missile(Vector2f location, float direction, Score::PLAYER player);
	virtual ~Missile();
	// Functions inherited from Drawable
	virtual float getDirection();
	virtual Vector2f getPosition();
	virtual RectSize getSize();
	// Update missile object
	void update();
	// Check if missile is Destroyable.
	bool isDestroyable(bool isHorizontal);
	// Check which player the missile was fired from
	Score::PLAYER getPlayer();
private:
	// Private member variables
	// Private member variables.
	Vector2f _velocity;
	Vector2f _position;
	RectSize _size;
	Angle _direction;
	float _pi;
	float _collisions;
	float _velocityModifier;
	Score::PLAYER _player;

	// Private helper functions
	bool isDestroyCone(float cone = 5);
};

#endif /* MISSILE_H_ */
