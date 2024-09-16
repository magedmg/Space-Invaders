#pragma once
#include "alien.hpp"
#include "laser.hpp"
#include "mysteryship.hpp"
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
  std::vector<Alien> aliens;
  std::vector<Alien> createAliens();
  ~Game();
  void MoveAliens();
  int direction;

  Mysteryship mysteryship;

  std::vector<Laser> alienLasers;
  void AlienShootLaser();
  float alienshiplaserinterval;

  int mysteryshipspawninterval;
  float timeLastSpawn;
};