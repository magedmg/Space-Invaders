#include "game.hpp"
#include "laser.hpp"
#include "obstacle.hpp"
#include "raylib.h"
#include "spaceship.hpp"
#include <vector>

#include <algorithm>
#include <iostream>
using namespace std;

Game::Game() {
  ship.Draw();

  // goes through each of the elements. auto means you dont have to specify the
  // type of each element. & uses a reference to the element to make the code
  // more efficient. this is because it takes the address and not a copy of each
  // one. add const so that the element is not modified in the loop
  for (auto &laser : ship.lasers) {
    laser.Draw();
  }
  obstacles = createObstacles();
}

void Game::updateAll() {
  ship.Draw();
  if (IsKeyDown(KEY_A)) {
    ship.MoveLeft();
    cout << "a ";
  }
  if (IsKeyDown(KEY_D)) {
    ship.MoveRight();
    cout << "d ";
  }

  if (IsKeyDown(KEY_SPACE)) {
    ship.FireLaser();
    cout << "space";
  }
  cout << endl;

  for (auto &laser : ship.lasers) {
    laser.Update();
    laser.Draw();
  }
  deleteInactiveLasers();
  std::cout << "Vector size: " << ship.lasers.size();
  // Laser::Update();

  for (auto &obstacle : obstacles) {
    obstacle.Draw();
  }
}

void Game::deleteInactiveLasers() {

  for (auto it = ship.lasers.begin(); it != ship.lasers.end();) {
    if (!it->active) {
      it = ship.lasers.erase(it);
    } else {
      ++it;
    }
  }
}

std::vector<Obstacle> Game::createObstacles() {

  int obstaclewidth = Obstacle::grid[0].size() * 3;

  float gap = (GetScreenWidth() - (4 * obstaclewidth)) / 5;

  for (int i = 0; i < 4; i++) {
    float offsetX = (i + 1) * gap + i * obstaclewidth;
    obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
  }
  return obstacles;
}