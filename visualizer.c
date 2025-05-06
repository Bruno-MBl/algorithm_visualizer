#include "raylib.h"
#include <stdio.h>
#include <unistd.h>

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

#define MAX_HIGHLIGHTS 2

int rectangle_heights[NUM_RECTANGLES];
int active_rectangle = 0;
int current_loop = 0;
int min;

struct highlight {
  int index;
  Color color;
};

void bubble_sort();
void select_sort();
void quickSort(int arr[], int low, int high);
void randomize();
void draw_rectangles(struct highlight[]);
void reset_highlights();
void swap(int *, int *);
int partition(int arr[], int low, int high);

struct highlight highlights[MAX_HIGHLIGHTS];

int main(void) {
  reset_highlights();
  randomize();
  int sorting = 0;
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sort algorithm visualizer");
  bool showMessageBox = false;

  SetTargetFPS(100);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (sorting <= 0) {
      draw_rectangles(NULL);
    }

    if (GuiButton((Rectangle){PADDING, PADDING, 200, 50}, "Sort"))
      showMessageBox = true;
    if (showMessageBox) {
      sorting = GuiMessageBox((Rectangle){85, 70, 250, 100}, "#191#Message Box",
                              "Sort Method", "Bubble sort;Selection Sort;Quick Sort");

      if (sorting >= 0)
        showMessageBox = false;
    }
    if (GuiButton((Rectangle){PADDING + 200 + PADDING, PADDING, 200, 50},
                  "Randomize"))
      randomize();

    char text[20];
    sprintf(text, "%d", current_loop);
    DrawText(text, 500, 20, 10, GRAY);
    if (sorting > 0) {
      if (sorting == 1)
        bubble_sort();
      else if (sorting == 2)
        select_sort();
      else if (sorting== 3)
        quickSort(rectangle_heights, 0, NUM_RECTANGLES-1);
      if (current_loop >= NUM_RECTANGLES) {
        sorting = 0;
        current_loop = 0;
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {

    // pi is the partition return index of pivot
    int pi = partition(arr, low, high);

    // Recursion calls for smaller elements
    // and greater or equals elements
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

int partition(int arr[], int low, int high) {

  int pivot = arr[high];

  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return i + 1;
}

void bubble_sort() {
  int temp;

  highlights[0].index = active_rectangle;
  highlights[0].color = RED;

  if (rectangle_heights[active_rectangle] >
      rectangle_heights[active_rectangle + 1]) {
    swap(&rectangle_heights[active_rectangle],
         &rectangle_heights[active_rectangle + 1]);
  }
  active_rectangle++;
  if (active_rectangle >= NUM_RECTANGLES - current_loop - 1) {
    active_rectangle = 0;
    current_loop++;
    reset_highlights();
  }
  draw_rectangles(highlights);
}

void select_sort() {
  int temp;

  highlights[0].index = active_rectangle;
  highlights[0].color = RED;

  if (rectangle_heights[active_rectangle] < rectangle_heights[min]) {
    min = active_rectangle;
    highlights[1].index = min;
    highlights[1].color = BLUE;
  }

  active_rectangle++;
  if (active_rectangle >= NUM_RECTANGLES) {
    swap(&rectangle_heights[current_loop], &rectangle_heights[min]);
    current_loop++;
    active_rectangle = current_loop;
    min = active_rectangle;
  }
  draw_rectangles(highlights);
}

void randomize() {
  srand(time(NULL));
  for (int i = 0; i < NUM_RECTANGLES; i++) {
    rectangle_heights[i] = rand() % MAX_HEIGHT + MIN_HEIGHT;
  }
  current_loop = 0;
  active_rectangle = 0;
  reset_highlights();
}

void draw_rectangles(struct highlight highlights[]) {
  for (int i = 0; i < NUM_RECTANGLES; i++) {
    Color color;
    if (i % 2 == 0)
      color = DARKGRAY;
    else
      color = GRAY;
    if (highlights != NULL) {
      for (int j = 0; j < MAX_HIGHLIGHTS; j++) {
        if (i == highlights[j].index) {
          color = highlights[j].color;
        }
      }
    }
    DrawRectangle(0 + PADDING + i * RECTANGLE_WIDHT,
                  SCREEN_HEIGHT - PADDING - rectangle_heights[i],
                  RECTANGLE_WIDHT, rectangle_heights[i], color);
  }
}
void reset_highlights() {
  for (int i = 0; i < MAX_HIGHLIGHTS; i++) {
    highlights[i].index = -1;
  }
}
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
