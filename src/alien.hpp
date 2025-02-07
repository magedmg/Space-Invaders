#pragma once

#include <raylib.h>

class Alien {
public:
  Alien(int type, Vector2 position);
  void Update(int direction);
  void Draw();
  int GetType();
  Texture2D Image;

  static Texture2D alienImages[3];

  static void UnloadImages();

  int type;
  Vector2 position;

  Rectangle getrect();

private:
};