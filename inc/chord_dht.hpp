#ifndef CHORD_DHT_HPP
#define CHORD_DHT_HPP

#include <cmath>

class ChordDht
{
public:
  int avoid_collision_formula(int avoid_collision_m)
  {
    return std::pow(2, avoid_collision_m) - 1;
  }

  int recorded_arc_formula(int recorded_arc)
  {
    return 2 * recorded_arc + 1;
  }
};

#endif // CHORD_DHT_HPP
