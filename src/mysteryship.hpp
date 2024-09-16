#pragma once

#include "raylib.h"
class Mysteryship {
public:
  Mysteryship();
  ~Mysteryship();
  void Update();
  void Draw();
  void Spawn();
  bool alive;

  Rectangle getrect();

private:
  Vector2 position;
  Texture2D image;
  int speed;
};