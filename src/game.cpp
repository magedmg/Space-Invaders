#include "game.hpp"
#include "alien.hpp"
#include "laser.hpp"
#include "obstacle.hpp"
#include "raylib.h"
#include "spaceship.hpp"
#include <vector>

#include <algorithm>
#include <iostream>
using namespace std;

Game::Game() { InitGame(); }

void Game::updateAll() {

  if (run) {
    double currentTime = GetTime();

    if (currentTime - timeLastSpawn > mysteryshipspawninterval) {
      mysteryship.Spawn();
      timeLastSpawn = GetTime();
      mysteryshipspawninterval = GetRandomValue(10, 20);
    }
    mysteryship.Draw();
    mysteryship.Update();

    ship.Draw();
    if (IsKeyDown(KEY_A)) {
      ship.MoveLeft();
    }
    if (IsKeyDown(KEY_D)) {
      ship.MoveRight();
    }

    if (IsKeyDown(KEY_SPACE)) {
      ship.FireLaser();
    }

    for (auto &laser : ship.lasers) {
      laser.Update();
      laser.Draw();
    }
    deleteInactiveLasers();
    // Laser::Update();

    for (auto &obstacle : obstacles) {
      obstacle.Draw();
    }

    for (auto &alien : aliens) {
      alien.Draw();
    }
    MoveAliens();
    AlienShootLaser();

    for (auto &alienlaser : alienLasers) {
      alienlaser.Draw();
      alienlaser.Update();
    }
    checkForCollisions();
  } else {
    if (IsKeyDown(KEY_SPACE)) {
      Reset();
      InitGame();
    }
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

  for (auto it = alienLasers.begin(); it != alienLasers.end();) {
    if (!it->active) {
      it = alienLasers.erase(it);

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
    obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
  }
  return obstacles;
}

std::vector<Alien> Game::createAliens() {
  std::vector<Alien> aliens;
  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 11; col++) {
      int alienType;
      if (row == 0) {
        alienType = 3;
      } else if (row == 1 || row == 2) {
        alienType = 2;
      } else {
        alienType = 1;
      }
      float x = 75 + col * 55;
      float y = 110 + row * 55;
      aliens.push_back(Alien(alienType, {x, y}));
    }
  }
  return aliens;
}

Game::~Game() { Alien::UnloadImages(); }

void Game::MoveAliens() {

  int movement = 1;

  if (direction == 1) {
    for (auto &alien : aliens) {
      alien.Update(movement);
    }
    if (aliens[10].position.x > GetScreenWidth() - 75) {
      direction = 0;
      for (auto &alien : aliens) {
        alien.position.y += 5;
      }
    }
  } else {
    for (auto &alien : aliens) {
      alien.Update(-movement);
    }
    if (aliens[0].position.x < 25) {
      direction = 1;
      for (auto &alien : aliens) {
        alien.position.y += 5;
      }
    }
  }
}

void Game::AlienShootLaser() {

  if (GetTime() - alienshiplaserinterval >= 0.35) {
    int randomindex = GetRandomValue(0, aliens.size() - 1);

    Alien &alien = aliens[randomindex];
    alienLasers.push_back(
        Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
               alien.position.y + alien.alienImages[alien.type - 1].height},
              6));
    alienshiplaserinterval = GetTime();
  }
}

void Game::checkForCollisions() {
  // Spaceship lasers
  for (auto &laser : ship.lasers) {
    auto it = aliens.begin();
    while (it != aliens.end()) {
      if (CheckCollisionRecs(it->getrect(), laser.getrec())) {
        it = aliens.erase(it);
        laser.active = false;
      } else {
        it++;
      }
    }
    for (auto &obstacle : obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it->getrect(), laser.getrec())) {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        } else {
          it++;
        }
      }
    }
    if (CheckCollisionRecs(mysteryship.getrect(), laser.getrec())) {
      mysteryship.alive = false;
      laser.active = false;
    }
  }
  // Alien lasers

  for (auto &laser : alienLasers) {
    if (CheckCollisionRecs(laser.getrec(), ship.getrect())) {
      lives--;
      if (lives < 1) {
        // ship.died();
        run = false;
      }
      laser.active = false;
    }

    for (auto &obstacle : obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it->getrect(), laser.getrec())) {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        } else {
          it++;
        }
      }
    }
  }

  for (auto &alien : aliens) {
    if (CheckCollisionRecs(alien.getrect(), ship.getrect())) {
      ship.died();
    }
    for (auto &obstacle : obstacles) {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end()) {
        if (CheckCollisionRecs(it->getrect(), alien.getrect())) {
          it = obstacle.blocks.erase(it);
        } else {
          it++;
        }
      }
    }
  }
}

void Game::Reset() {
  ship.Reset();
  aliens.clear();
  alienLasers.clear();
  obstacles.clear();
}

// this was copied from the constructor
void Game::InitGame() {
  ship.Draw();

  // goes through each of the elements. auto means you dont have to specify the
  // type of each element. & uses a reference to the element to make the code
  // more efficient. this is because it takes the address and not a copy of each
  // one. add const so that the element is not modified in the loop
  for (auto &laser : ship.lasers) {
    laser.Draw();
  }
  obstacles = createObstacles();
  aliens = createAliens();
  direction = 1;
  alienshiplaserinterval = 0;
  mysteryshipspawninterval = GetRandomValue(10, 20);
  timeLastSpawn = 0.0;
  lives = 3;
  run = true;
}