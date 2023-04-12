#ifndef CHORD_DHT_RING_HPP
#define CHORD_DHT_RING_HPP

#include "C:/raylib/raylib/src/raylib.h"

#define MINIMUM_SEGMENTED_NODES (10)

class ChordNode
{
public:
  Vector2 position;
  float radius;

  void init_chord_nodes()
  {
    ChordNode nodes[MINIMUM_SEGMENTED_NODES] = {0};

    for (auto i = 0; i < MINIMUM_SEGMENTED_NODES; i++)
    {
      nodes[i].position.x = (float)GetRandomValue((int)nodes[i].radius, (int)(GetScreenWidth() - nodes[i].radius));
      nodes[i].position.y = (float)GetRandomValue((int)nodes[i].radius, (int)(GetScreenHeight() - nodes[i].radius));
    }
  }
};

#endif // CHORD_DHT_RING_HPP