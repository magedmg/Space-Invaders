#include "game.hpp"
#include "laser.hpp"
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