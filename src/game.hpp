#pragma once
#include "laser.hpp"
#include "spaceship.hpp"

class Game {

public:
  Spaceship ship;
  void deleteInactiveLasers();
  Game();
  void updateAll();
};