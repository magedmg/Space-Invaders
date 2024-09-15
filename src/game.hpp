#pragma once
#include "laser.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"

class Game {

public:
  Spaceship ship;
  void deleteInactiveLasers();
  std::vector<Obstacle> createObstacles();
  Game();
  void updateAll();
  std::vector<Obstacle> obstacles;
};