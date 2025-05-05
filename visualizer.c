#include "raylib.h"
#include <stdio.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define NUM_RECTANGLES 50
#define PADDING 10
#define RECTANGLE_WIDHT (SCREEN_WIDTH - PADDING * 2) / NUM_RECTANGLES
#define MAX_HEIGHT 700
#define MIN_HEIGHT 70

int rectangle_heights[NUM_RECTANGLES];
int active_rectangle = 0;
int current_loop = 0;

void bubble_sort();
void randomize();

int main(void) {
  randomize();
  int sorting = 0;
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sort algorithm visualizer");

  SetTargetFPS(90);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (GuiButton((Rectangle){PADDING, PADDING, 200, 50}, "Sort"))
      sorting = (sorting + 1) % 2;
    if (GuiButton((Rectangle){PADDING + 200 + PADDING, PADDING, 200, 50},
                  "Randomize"))
      randomize();

    for (int i = 0; i < NUM_RECTANGLES; i++) {
      Color color;
      if (active_rectangle == i && sorting == 1)
        color = RED;
      else if (i % 2 == 0)
        color = DARKGRAY;
      else
        color = GRAY;
      DrawRectangle(0 + PADDING + i * RECTANGLE_WIDHT,
                    SCREEN_HEIGHT - PADDING - rectangle_heights[i],
                    RECTANGLE_WIDHT, rectangle_heights[i], color);
    }
    char text[20];
    sprintf(text, "%d", current_loop);
    DrawText(text, 500, 20, 10, GRAY);
    if (sorting == 1) {
      bubble_sort();
      active_rectangle++;
      if (current_loop >= NUM_RECTANGLES) {
        sorting = 0;
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void bubble_sort() {
  int temp;
  if (active_rectangle >= NUM_RECTANGLES - current_loop - 1) {
    active_rectangle = 0;
    current_loop++;
  }
  if (active_rectangle + 1 >= NUM_RECTANGLES) {
    return;
  }
  if (rectangle_heights[active_rectangle] >
      rectangle_heights[active_rectangle + 1]) {
    temp = rectangle_heights[active_rectangle];
    rectangle_heights[active_rectangle] =
        rectangle_heights[active_rectangle + 1];
    rectangle_heights[active_rectangle + 1] = temp;
  }
}
void randomize() {
  srand(time(NULL));
  for (int i = 0; i < NUM_RECTANGLES; i++) {
    rectangle_heights[i] = rand() % MAX_HEIGHT + MIN_HEIGHT;
  }
  current_loop = 0;
  active_rectangle = 0;
}
