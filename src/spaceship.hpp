#pragma once

#include "laser.hpp"
#include <raylib.h>
#include <vector>

class Spaceship {
public:
  Spaceship();
  ~Spaceship();
  void Draw();
  void MoveLeft();
  void MoveRight();
  void FireLaser();
  std::vector<Laser> lasers;

  Rectangle getrect();

  bool alive;

  void died();
  void Reset();

private:
  Texture2D image;
  Vector2 position; // vector that holds 2 things and in this case thats x and y
  double lastFiredTime;
};
