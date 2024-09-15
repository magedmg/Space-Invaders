
#include "block.cpp"
#include "block.hpp"
#include "game.cpp"
#include "game.hpp"
#include "laser.cpp"
#include "laser.hpp"
#include "obstacle.cpp"
#include "obstacle.hpp"
#include "spaceship.cpp"
#include "spaceship.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

int main() {

  Color grey = {29, 29, 27, 255}; // colour is a struct here, called grey

  int windowWidth = 750;
  int windowHeight = 700;

  InitWindow(windowWidth, windowHeight, "Space Invadors");

  SetTargetFPS(60); // while loop will be faster without a target fps (which
                    // means it will look different on machines )

  Game game; // draws the spaceeship to the screen
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(grey); // every frame there is a new clear background so
                           // that there isnt old artifacts from previous frames
    game.updateAll();
    EndDrawing();
  }

  CloseWindow(); // if you open a window you have to close it at some point (so
                 // when the program ends)
  return 0;
}