#include "mysteryship.hpp"
#include "raylib.h"

Mysteryship::Mysteryship() {
  this->alive = false;
  image = LoadTexture("Graphics/mystery.png");
}

Mysteryship::~Mysteryship() { UnloadTexture(image); }

void Mysteryship::Spawn() {
  position.y = 90;
  int side = GetRandomValue(0, 1);
  if (side == 0) {
    position.x = 0;
    speed = 3;
  } else {
    position.x = GetScreenWidth() - image.width;
    speed = -3;
  }
  alive = true;
}

void Mysteryship::Update() {
  if (alive) {
    position.x += speed;
    if (position.x > GetScreenWidth() - image.width || position.x < 0) {
      alive = false;
    }
  }
}

void Mysteryship::Draw() {
  if (alive) {
    DrawTextureV(image, position, WHITE);
  }
}

Rectangle Mysteryship::getrect() {
  if (alive) {
    return {position.x, position.y, float(image.width), float(image.height)};
  } else {
    return {position.x, position.y, 0.0, 0.0};
  }
}