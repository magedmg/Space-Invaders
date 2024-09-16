#include "spaceship.hpp"
#include "raylib.h"
#include <time.h>
#include <vector>

Spaceship::Spaceship() {
  image = LoadTexture("Graphics/spaceship.png");
  position.x = (GetScreenWidth() - image.width) / 2.0;
  position.y = GetScreenHeight() - image.height;
  this->lastFiredTime = 0;
  alive = true;
}

Spaceship::~Spaceship() {
  UnloadTexture(image);
} // need to unload the image once the game has finished to free up memory

void Spaceship::Draw() {
  if (alive) {
    DrawTextureV(image, position, WHITE);
  }
  // draws a texture to a certain position
  // and the position is held in a vector
}

void Spaceship::MoveLeft() {
  /*if (position.x != GetScreenWidth() - image.width &&
      position.y != GetScreenHeight() - image.height) {
    position.x -= 10;
    DrawTextureV(image, position, WHITE);
  }
  */
  position.x -= 10;

  if (position.x < 0) {
    position.x = 0;
  }

  // DrawTextureV(image, position, WHITE);
}
void Spaceship::MoveRight() {

  position.x += 10;
  if (position.x > GetScreenWidth() - image.width) {
    position.x = GetScreenWidth() - image.width;
  }
  // DrawTextureV(image, position, WHITE);
}

void Spaceship::FireLaser() {
  if (GetTime() - lastFiredTime >= 0.35) {
    lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6));
    lastFiredTime = GetTime();
  }
}

Rectangle Spaceship::getrect() {
  return {position.x, position.y, float{static_cast<float>(image.width)},
          float{static_cast<float>(image.height)}};
}

void Spaceship::died() {
  alive = false;
  // UnloadTexture(image);
}

void Spaceship::Reset() {
  position.x = (GetScreenWidth() - image.width) / 2.0;
  position.y = GetScreenHeight() - image.height;
  DrawTextureV(image, position, WHITE);
  lasers.clear();
}