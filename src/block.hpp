#pragma once

#include <raylib.h>

class Block {
public:
  Block(Vector2 position);

  void Draw();

  Rectangle getrect();

private:
  Vector2 position;
};