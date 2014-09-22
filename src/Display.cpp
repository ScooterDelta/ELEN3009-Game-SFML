#include "Display.h"

Display::Display(RenderWindow * window) :
	_window{window},
	_hud{window},
	_mineLight{false}
{
	initializeTank();
	initializeMissile();
	initializeExplosion();
	initializeObstacle();
	initializeMine();
	initializeBackGround();
}

void Display::drawBackGround()
{
	_window->draw(_drawBackGround);
}

void Display::draw(Tank & tank, Score::PLAYER player)
{
	if (player == Score::PLAYER1)
	{
		_drawPlayer1Tank.setPosition({tank.getPosition().x, tank.getPosition().y});
		_drawPlayer1Tank.setRotation(tank.getDirection());

		_window->draw(_drawPlayer1Tank);
	}
	else
	{
		_drawPlayer2Tank.setPosition({tank.getPosition().x, tank.getPosition().y});
		_drawPlayer2Tank.setRotation(tank.getDirection());

		_window->draw(_drawPlayer2Tank);
	}
	_hud.DrawUI(tank, player);
}

void Display::draw(std::list<std::unique_ptr<Missile>> * missile)
{
	Vector2f tempVect;
	auto _missileIterator = missile->begin();
	while(_missileIterator != missile->end())
	{
		tempVect = {(*_missileIterator)->getPosition().x, (*_missileIterator)->getPosition().y};
		_drawMissile.setPosition(tempVect);
		_drawMissile.setRotation((*_missileIterator)->getDirection());

		_window->draw(_drawMissile);
		++_missileIterator;
	}

}

void Display::draw(std::list<std::unique_ptr<Explosion>> * explosion)
{
	Vector2f tempVect;
	auto _explosionIterator = explosion->begin();
	while(_explosionIterator != explosion->end())
	{
		tempVect = {(*_explosionIterator)->getPosition().x, (*_explosionIterator)->getPosition().y};
		_drawExplosion.setPosition(tempVect);

		_window->draw(_drawExplosion);
		++_explosionIterator;
	}
}

void Display::draw(std::list<std::unique_ptr<Obstacle>> * obstacle)
{
	Vector2f tempVect;
	auto _obstacleIterator = obstacle->begin();
	while (_obstacleIterator != obstacle->end())
	{
		tempVect = {(*_obstacleIterator)->getPosition().x, (*_obstacleIterator)->getPosition().y};
		_drawObstacle.setPosition(tempVect);

		if((*_obstacleIterator)->getTexture() == Obstacle::BOX)
		{
			if((*_obstacleIterator)->remainingHits() == 0)
				_drawObstacle.setTexture(&_obstacleTextureBox4, true);
			else if((*_obstacleIterator)->remainingHits() == 1)
				_drawObstacle.setTexture(&_obstacleTextureBox3, true);
			else if((*_obstacleIterator)->remainingHits() == 2)
				_drawObstacle.setTexture(&_obstacleTextureBox2, true);
			else
				_drawObstacle.setTexture(&_obstacleTextureBox1, true);
		}
		else if ((*_obstacleIterator)->getTexture() == Obstacle::BRICK)
		{
			if((*_obstacleIterator)->remainingHits() == 0)
				_drawObstacle.setTexture(&_obstacleTextureBrick4, true);
			else if((*_obstacleIterator)->remainingHits() == 1)
				_drawObstacle.setTexture(&_obstacleTextureBrick3, true);
			else if((*_obstacleIterator)->remainingHits() == 2)
				_drawObstacle.setTexture(&_obstacleTextureBrick2, true);
			else
				_drawObstacle.setTexture(&_obstacleTextureBrick1, true);
		}


		_window->draw(_drawObstacle);
		++_obstacleIterator;
	}
}

void Display::draw(std::list<std::unique_ptr<Mine>> * mine)
{
	Vector2f tempVect;
	_mineTime++;
	if(_mineTime % 30 == 0)
		_mineLight = !_mineLight;
	auto _mineIterator = mine->begin();
	while (_mineIterator != mine->end())
	{
		if(_mineLight)
		{
			tempVect = {(*_mineIterator)->getPosition().x, (*_mineIterator)->getPosition().y};
			_drawMine1.setPosition(tempVect);

			_window->draw(_drawMine1);
		}
		else
		{
			tempVect = {(*_mineIterator)->getPosition().x, (*_mineIterator)->getPosition().y};
			_drawMine2.setPosition(tempVect);

			_window->draw(_drawMine2);
		}

		++_mineIterator;
	}
}

void Display::draw(Score & _score, bool isPaused)
{
	_hud.DrawScore(_score, isPaused);
}

void Display::draw(float remainingTime)
{
	_hud.DrawTimer(remainingTime);
}

void Display::initializeTank()
{
	_player1TankTexture.loadFromFile("assets/tank1.png");
	_drawPlayer1Tank.setTexture(_player1TankTexture, true);
	_player2TankTexture.loadFromFile("assets/tank2.png");
	_drawPlayer2Tank.setTexture(_player2TankTexture, true);

	_drawPlayer1Tank.setOrigin(760.f, _drawPlayer1Tank.getGlobalBounds().height/2);
	_drawPlayer2Tank.setOrigin(760.f, _drawPlayer2Tank.getGlobalBounds().height/2);

	//_drawPlayer1Tank.setOrigin(_drawPlayer1Tank.getGlobalBounds().width/2, _drawPlayer1Tank.getGlobalBounds().height/2);
	_drawPlayer1Tank.setScale(0.04 * (_window)->getSize().x/1600, 0.04 * (_window)->getSize().y/900);
	//_drawPlayer2Tank.setOrigin(_drawPlayer2Tank.getGlobalBounds().width/2, _drawPlayer2Tank.getGlobalBounds().height/2);
	_drawPlayer2Tank.setScale(0.04 * (_window)->getSize().x/1600, 0.04 * (_window)->getSize().y/900);
}

void Display::initializeMissile()
{
	_missileTexture.loadFromFile("assets/projectile1.png");
	_drawMissile.setTexture(_missileTexture, true);
	_drawMissile.setOrigin(_drawMissile.getGlobalBounds().width/2, _drawMissile.getGlobalBounds().height/2);
	_drawMissile.setScale(0.025 * (_window)->getSize().x/1600, 0.025 * (_window)->getSize().y/900);
}

void Display::initializeExplosion()
{
	// Initialize mine texture.
	Vector2f windowSize{_window->getSize()};

	_explosionTexture.loadFromFile("assets/explosion.png");
	_drawExplosion.setTexture(_explosionTexture, true);
	_drawExplosion.setOrigin(_drawExplosion.getGlobalBounds().width/2, _drawExplosion.getGlobalBounds().height/2);
	_drawExplosion.setScale(0.06 * windowSize.x / 1600, 0.06 * windowSize.y / 900);
}

void Display::initializeObstacle()
{
	// Need to initialize texture here.
	_drawObstacle.setRotation(0);
	Vector2f windowSize{_window->getSize()};
	_drawObstacle.setSize({windowSize.x/32, windowSize.y/18});
	_drawObstacle.setOrigin({0.f, 0.f});

	_obstacleTextureBox1.loadFromFile("assets/box1.png");
	_obstacleTextureBox2.loadFromFile("assets/box2.png");
	_obstacleTextureBox3.loadFromFile("assets/box3.png");
	_obstacleTextureBox4.loadFromFile("assets/box4.png");
	_obstacleTextureBrick1.loadFromFile("assets/brick1.png");
	_obstacleTextureBrick2.loadFromFile("assets/brick2.png");
	_obstacleTextureBrick3.loadFromFile("assets/brick3.png");
	_obstacleTextureBrick4.loadFromFile("assets/brick4.png");
}

void Display::initializeMine()
{
	// Initialize mine texture.
	Vector2f windowSize{_window->getSize()};

	_mineTexture1.loadFromFile("assets/mine1.png");
	_mineTexture2.loadFromFile("assets/mine2.png");
	_drawMine1.setTexture(_mineTexture1, true);
	_drawMine1.setOrigin(_drawMine1.getGlobalBounds().width/2, _drawMine1.getGlobalBounds().height/2);
	_drawMine1.setScale(0.05 * windowSize.x / 1600, 0.05 * windowSize.y / 900);
	_drawMine2.setTexture(_mineTexture2, true);
	_drawMine2.setOrigin(_drawMine2.getGlobalBounds().width/2, _drawMine2.getGlobalBounds().height/2);
	_drawMine2.setScale(0.05 * windowSize.x / 1600, 0.05 * windowSize.y / 900);
}

void Display::initializeBackGround()
{
	Vector2f windowSize{_window->getSize()};
	// Initialize the background testure.
	_backGroundTexture.loadFromFile("assets/backdrop.png");
	_drawBackGround.setTexture(_backGroundTexture, true);
	_drawBackGround.setOrigin(0,0);
	_drawBackGround.setScale(windowSize.x/3200, windowSize.y/1800);
	_drawBackGround.setPosition(0,0);
}
