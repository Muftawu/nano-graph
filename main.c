#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FPS 60
#define width 1000
#define height 900
#define tick_len 12
#define center                                                                 \
  (Vector2) { 0.5 * width, 0.5 * height }

float scale(float x) { return x / 2; }

void plot_grid(int ticks_per_axes) {
  // ticks
  int half_axes_height = (int)(0.5 * height);

  // axes
  // Vector2 center = (Vector2){0.5 * width, 0.5 * height};

  // y-coords
  Vector2 y_axes[2] = {
      (Vector2){0.5 * width, 0},
      (Vector2){0.5 * width, height},
  };

  // x-coords
  Vector2 x_axes[2] = {
      (Vector2){0, 0.5 * height},
      (Vector2){width, 0.5 * height},
  };

  // center
  DrawCircle(center.x, center.y, 10, BLUE);

  // y-axes
  DrawLine(y_axes[0].x, y_axes[0].y, y_axes[1].x, y_axes[1].y, BLUE);
  // x-axes
  DrawLine(x_axes[0].x, x_axes[0].y, x_axes[1].x, x_axes[1].y, BLUE);

  // unit ticking (y-axes)
  for (int i = 0; i < ticks_per_axes; i++) {

    Vector2 top_left_vec =
        (Vector2){center.x - tick_len, center.y - (i * tick_len)};
    Vector2 top_right_vec =
        (Vector2){center.x + tick_len, center.y - (i * tick_len)};

    Vector2 bottom_left_vec =
        (Vector2){center.x - tick_len, center.y + (i * tick_len)};
    Vector2 bottom_right_vec =
        (Vector2){center.x + tick_len, center.y + (i * tick_len)};

    DrawLine(top_left_vec.x, top_left_vec.y, top_right_vec.x, top_right_vec.y,
             BLUE);
    DrawLine(bottom_left_vec.x, bottom_left_vec.y, bottom_right_vec.x,
             bottom_right_vec.y, BLUE);
  }

  // unit ticking (x-axis)
  for (int i = 0; i < ticks_per_axes; i++) {

    Vector2 left_top_vec =
        (Vector2){center.x - (i * tick_len), center.y + tick_len};
    Vector2 left_bottom_vec =
        (Vector2){center.x - (i * tick_len), center.y - tick_len};

    Vector2 right_top_vec =
        (Vector2){center.x + (i * tick_len), center.y - tick_len};
    Vector2 right_bottom_vec =
        (Vector2){center.x + (i * tick_len), center.y + tick_len};

    DrawLine(left_top_vec.x, left_top_vec.y, left_bottom_vec.x,
             left_bottom_vec.y, BLUE);
    DrawLine(right_top_vec.x, right_top_vec.y, right_bottom_vec.x,
             right_bottom_vec.y, BLUE);
  }
}

void plot_line(float m, float c) {
  // y = mx + c
  float x = 0.0f;
  float y = 0.0f;
  float x_intercept_val = (y - c) / (m);

  const char *eq = TextFormat("y = (%.2f)x + %.2f \n", m, c);
  const char *x_intercept =
      TextFormat("x-intercept = (%.2f) \n", x_intercept_val);
  const char *y_intercept = TextFormat("y-intercept = (%.2f) \n", c);

  int interpolation_rate = 2;

  Vector2 line_point_1 =
      (Vector2){center.x + (x_intercept_val * tick_len), center.y};
  Vector2 line_point_2 = (Vector2){center.x, center.y + (-c * tick_len)};

  // interpolation
  float x_new_val1 = (line_point_1.x);
  float y_new_val1 = ((m * x_new_val1) + c);

  printf("(x1, y1) => (%f, %f) \n", line_point_1.x, line_point_1.y);
  printf("(x2, y2) => (%f, %f) \n", x_new_val1, y_new_val1);
  // printf("(x2, y2) => (%f, %f) \n", line_point_2.x, line_point_2.y);

  // float x_new_val2 = line_point_2.x * 2;
  // float y_new_val2 = (m * x_new_val2) + c;

  Vector2 interpolation1 =
      (Vector2){x_new_val1 * tick_len, y_new_val1 * tick_len};
  // Vector2 interpolation2 = (Vector2){x_new_val2, y_new_val2};

  // printf("(x-new-val, y-new-val) => (%f, %f) \n", interpolation1.x,
  //        interpolation1.y);
  // printf("%f, %f \n", interpolation2.x, interpolation2.y);

  DrawText(eq, 0.05 * width, 0.05 * height, 20, RAYWHITE);
  DrawText(y_intercept, 0.05 * width, 0.10 * height, 20, RAYWHITE);
  DrawText(x_intercept, 0.05 * width, 0.15 * height, 20, RAYWHITE);

  // intercept points (real values)
  DrawCircle(line_point_1.x, line_point_1.y, 5, RAYWHITE);
  DrawCircle(line_point_2.x, line_point_2.y, 5, RAYWHITE);

  // interpolation points
  DrawCircle(interpolation1.x, interpolation1.y, 5, YELLOW);
  // DrawCircle(interpolation2.x, interpolation2.y, 5, YELLOW);

  // // line connecting points
  DrawLine(line_point_1.x, line_point_1.y, line_point_2.x, line_point_2.y,
           RAYWHITE);

  // DrawLine(interpolation_point1.x, interpolation_point1.y,
  //          interpolation_point2.x, interpolation_point2.y, RAYWHITE);
}

int main() {

  InitWindow(width, height, "Nano Graph");
  SetTargetFPS(FPS);

  const char **equation = "y = 2x+5";

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    plot_grid((int)(0.5 * width));
    plot_line(2, 5);

    EndDrawing();
  }

  CloseWindow();
}
