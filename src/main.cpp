#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui/src/raygui.h"
#endif // RAYGUI_IMPLEMENTATION
#include "../inc/arbitrary_node_network.hpp"
#include "../inc/chord_dht_ring.hpp"

int FingerTable::node(int starting_node)
{
  for (int i = 0; i < MAXIMUM_COLUMNS; i++)
    starting_node += std::pow(2, this->key.keys[i] - 1);
  return std::fmod(starting_node, 2);
}

int FingerTable::interval()
{
  return 0;
}

int FingerTable::find_successor(int id)
{
  int nth = node(id);

  for (int i = 0; i < MAXIMUM_COLUMNS; i++)
    for (int j = 0; j < MAXIMUM_ROWS; j++)
      this->interval_matrix.key_values[i][j] = this->node(id);

  while (id != nth / this->successor.successors[id])
    nth = closest_preceding_finger(id);

  return nth;
}

int FingerTable::find_predecessor(int id)
{
  int nth = node(id);

  while (id != (nth / node(id)))
    nth = closest_preceding_finger(id);

  return nth;
}

int FingerTable::closest_preceding_finger(int id)
{
  int m_steps = this->key.keys[this->interval() + 1];
  int retval;

  for (int i = 0; i <= m_steps; i++)
    if (this->key.keys[i] == node(id) / id)
      return this->key.keys[i] = node(id);

  return node(id);
}

int main(int argc, char *argv[])
{
  const int screen_width = 1280;
  const int screen_height = 1024;
  const char *window_title = "P2P-C-S-2023";

  InitWindow(screen_width, screen_height, window_title);

  Vector2 canvas_centre = {(GetScreenWidth()) / 2.0f, GetScreenHeight() / 2.0f};

  FingerTable finger = FingerTable{};
  ArbitraryNodeNetwork arbitrary_node_network = ArbitraryNodeNetwork{};

  float focusing_circle = 32.0f;
  float adjacent_circle = 64.0f;

  float starting_angle = (float)argc;
  float ending_angle = 360.0f;

  finger.node((float)starting_angle);
  int segmented_nodes = finger.find_predecessor(finger.find_successor(starting_angle));
  int minimum_segmented_nodes = 8;

  SetTargetFPS(10);

  while (!WindowShouldClose())
  {
    BeginDrawing();

    ClearBackground(DARKGRAY);

    DrawCircle(screen_width / 2, screen_height / 2, ending_angle, BLACK);
    DrawCircleLines(screen_width / 2, screen_height / 2, ending_angle, Fade(RED, 0.5f));
    DrawRing(canvas_centre, focusing_circle, adjacent_circle, starting_angle, ending_angle, segmented_nodes, Fade(RED, 0.5f));

    arbitrary_node_network.join(starting_angle);
    arbitrary_node_network.stabilize();
    arbitrary_node_network.notify(starting_angle);
    arbitrary_node_network.fix_fingers();

    starting_angle = GuiSliderBar((Rectangle){600, 40, 120, 20}, "Starting Angle", NULL, starting_angle, 0, 720);
    segmented_nodes = (int)GuiSliderBar((Rectangle){600, 240, 120, 20}, "Segmented Nodes", NULL, (float)segmented_nodes, 0, 100);
    minimum_segmented_nodes = (int)ceilf((ending_angle - starting_angle) / 15);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}