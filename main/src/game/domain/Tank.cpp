// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Tank.h

#include "Tank.h"

namespace game::domain {

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  Tank::Tank(Vector2D position, Score::PLAYER player, Vector2D ScreenSize) :
    NonAxisAligned{position, 90, {30 * ScreenSize.x / 1600.f, 30 * ScreenSize.y / 900.f}},
    _pi{(const float) (atan(1) * 4)},
    _velocityModifier{0},
    _angleModifier{0},
    _allowedMines{3},
    _allowedInvis{1},
    _spawnDirection{90},
    _spawnLocation{position},
    _player{player},
    _invisibilityTimer{high_resolution_clock::now()} {}

  void Tank::setMovement(Movement movement, bool isHorizontal, float Magnitude) {
    switch (movement) {
    case NONE:
      if (Magnitude == 0)
        _velocityModifier = 0;
      else {
        if (_velocityModifier < -0.4)
          _velocityModifier += 0.2;
        else if (_velocityModifier > 0.4)
          _velocityModifier -= 0.2;
        else
          _velocityModifier = 0;
        DrawableObject::_position.x +=
          -_velocityModifier * cos(DrawableObject::_direction.getAngle() * _pi / 180);
        DrawableObject::_position.y +=
          -_velocityModifier * sin(DrawableObject::_direction.getAngle() * _pi / 180);
      }
      break;
    case FORWARD:
      // Move in the current direction.
      if (Magnitude < 1) {
        DrawableObject::_position.x += -Magnitude * cos(DrawableObject::_direction.getAngle() * _pi / 180);
        DrawableObject::_position.y += -Magnitude * sin(DrawableObject::_direction.getAngle() * _pi / 180);
      } else {
        if (_velocityModifier < 0)
          _velocityModifier = 0;
        if (_velocityModifier < Magnitude)
          _velocityModifier += 0.2;
        DrawableObject::_position.x +=
          -_velocityModifier * cos(DrawableObject::_direction.getAngle() * _pi / 180);
        DrawableObject::_position.y +=
          -_velocityModifier * sin(DrawableObject::_direction.getAngle() * _pi / 180);
      }
      break;
    case BACKWARD:
      // Move in the reverse of the current direction.
      if (Magnitude < 1) {
        DrawableObject::_position.x += Magnitude * cos(DrawableObject::_direction.getAngle() * _pi / 180);
        DrawableObject::_position.y += Magnitude * sin(DrawableObject::_direction.getAngle() * _pi / 180);
      } else {
        if (_velocityModifier > 0)
          _velocityModifier = 0;
        if (_velocityModifier > -Magnitude)
          _velocityModifier -= 0.2;
        DrawableObject::_position.x +=
          -_velocityModifier * cos(DrawableObject::_direction.getAngle() * _pi / 180);
        DrawableObject::_position.y +=
          -_velocityModifier * sin(DrawableObject::_direction.getAngle() * _pi / 180);
      }
      break;
    case FORWARDOBSTACLE:
      _velocityModifier = Magnitude / 2;
      if (!isHorizontal)
        DrawableObject::_position.y +=
          -Magnitude / 2 * sin(DrawableObject::_direction.getAngle() * _pi / 180);
      else
        DrawableObject::_position.x +=
          -Magnitude / 2 * cos(DrawableObject::_direction.getAngle() * _pi / 180);
      break;
    case BACKWARDOBSTACLE:
      _velocityModifier = -Magnitude / 2;
      if (!isHorizontal)
        DrawableObject::_position.y +=
          Magnitude / 2 * sin(DrawableObject::_direction.getAngle() * _pi / 180);
      else
        DrawableObject::_position.x +=
          Magnitude / 2 * cos(DrawableObject::_direction.getAngle() * _pi / 180);
      break;
    default:
      break;
    }
  }

  void Tank::setMovement(Direction direction, float Magnitude) {
    switch (direction) {
    case CLOCKWISE:
      // Rotate the sprite clockwise
      if (_angleModifier < 0)
        _angleModifier = 0;
      if (_angleModifier < Magnitude)
        _angleModifier += 0.4;
      DrawableObject::_direction += _angleModifier;
      break;
    case ANTICLOCKWISE:
      // Rotate the sprite anticlockwise
      if (_angleModifier > 0)
        _angleModifier = 0;
      if (_angleModifier > -Magnitude)
        _angleModifier -= 0.4;
      DrawableObject::_direction += _angleModifier;
      break;
    case STRAIGHT:
      _angleModifier = 0;
      break;
    }
  }

  int Tank::getAllowedMines() {
    return _allowedMines;
  }

  void Tank::plantMine() {
    _allowedMines--;
  }

  Score::PLAYER Tank::getPlayer() {
    return _player;
  }

  void Tank::respawn() {
    DrawableObject::_position = _spawnLocation;
    DrawableObject::_direction = _spawnDirection;
    _velocityModifier = 0;
    _allowedMines = 3;
    _allowedInvis = 1;
    _invisibilityTimer = high_resolution_clock::now();
  }

  // Turn the tank invisible
  void Tank::turnInvisible() {
    if (_allowedInvis > 0) {
      _invisibilityTimer = high_resolution_clock::now();
      _allowedInvis--;
    }

  }

  // Check if the tank is invisible
  bool Tank::isInvisible() {
    return duration_cast<milliseconds>( high_resolution_clock::now() - _invisibilityTimer ).count() < 5000;
  }
}
