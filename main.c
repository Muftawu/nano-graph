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

float unit_to_pixel(float val) { return center.x + (tick_len * val); }

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

void plot_line(float m, float c, Color lineColor, int showInterpolation) {
  // y = mx + c
  float x = 0.0f;
  float y = 0.0f;
  float interpolation_rate = 2.0f;
  float x_intercept_val = (y - c) / (m);

  // original line intercept points
  Vector2 line_intercept_point1 =
      (Vector2){center.x + (x_intercept_val * tick_len), center.y};
  Vector2 line_intercept_point2 =
      (Vector2){center.x, center.y + (-c * tick_len)};

  // interpolation line poitns
  float interpolation_val_x1 = x_intercept_val * interpolation_rate;
  float interpolation_val_x2 = interpolation_val_x1 * -1;

  Vector2 line_interpolation_point1 =
      (Vector2){center.x + (tick_len * interpolation_val_x1),
                center.y + (((m * interpolation_val_x1) + c) * -tick_len)};
  Vector2 line_interpolation_point2 =
      (Vector2){center.x + (tick_len * interpolation_val_x2),
                center.y + (((m * interpolation_val_x2) + c) * -tick_len)};

  // graph texts
  const char *pu_ratio =
      TextFormat("1 unit = %.2f pixels \n", unit_to_pixel(1));
  const char *eq = TextFormat("y = (%.2f)x + %.2f \n", m, c);
  const char *x_intercept =
      TextFormat("x-intercept = (%.2f) \n", x_intercept_val);
  const char *y_intercept = TextFormat("y-intercept = (%.2f) \n", c);
  const char *intercept_label_x = TextFormat(
      "(%.2f, %.2f) \n", line_intercept_point1.x, line_intercept_point1.y);
  const char *intercept_label_y = TextFormat(
      "(%.2f, %.2f) \n", line_intercept_point2.x, line_intercept_point2.y);
  float intercept_label_offset = 3;

  // pixel-to-unit-ratio
  DrawText(pu_ratio, 0.80 * width, 0.05 * height, 20, RAYWHITE);
  DrawText(eq, 0.05 * width, 0.05 * height, 20, RAYWHITE);
  DrawText(y_intercept, 0.05 * width, 0.10 * height, 20, RAYWHITE);
  DrawText(x_intercept, 0.05 * width, 0.15 * height, 20, RAYWHITE);

  DrawText(intercept_label_x, line_intercept_point1.x + intercept_label_offset,
           line_intercept_point1.y + intercept_label_offset, 20, RAYWHITE);
  DrawText(intercept_label_y, line_intercept_point2.x + intercept_label_offset,
           line_intercept_point2.y + intercept_label_offset, 20, RAYWHITE);

  // line intercept points (real values)
  DrawCircle(line_intercept_point1.x, line_intercept_point1.y, 5, RAYWHITE);
  DrawCircle(line_intercept_point2.x, line_intercept_point2.y, 5, RAYWHITE);
  DrawLine(line_interpolation_point1.x, line_interpolation_point1.y,
           line_interpolation_point2.x, line_interpolation_point2.y, RAYWHITE);

  // line interpolation points
  if (showInterpolation) {
    float interpolation_offset = 2;
    const char *interpolation_label_x =
        TextFormat("(%.2f, %.2f) \n", line_interpolation_point1.x,
                   line_interpolation_point1.y);
    const char *interpolation_label_y =
        TextFormat("(%.2f, %.2f) \n", line_interpolation_point2.x,
                   line_interpolation_point2.y);
    DrawText(interpolation_label_x,
             line_interpolation_point1.x + intercept_label_offset,
             line_interpolation_point1.y + intercept_label_offset, 20,
             RAYWHITE);
    DrawText(
        intercept_label_y, line_interpolation_point2.x + intercept_label_offset,
        line_interpolation_point2.y + intercept_label_offset, 20, RAYWHITE);

    DrawCircle(line_interpolation_point1.x, line_interpolation_point1.y, 5,
               RAYWHITE);
    DrawCircle(line_interpolation_point2.x, line_interpolation_point2.y, 5,
               RAYWHITE);
  }

  // prints
  printf("unit to pixel: %f => %f \n", -5.0f, unit_to_pixel(-5));
}

int main() {

  InitWindow(width, height, "Nano Graph");
  SetTargetFPS(FPS);

  const char **equation = "y = 2x+5";

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    plot_grid((int)(0.5 * width));
    plot_line(2, 5, RAYWHITE, 1);

    EndDrawing();
  }

  CloseWindow();
}
