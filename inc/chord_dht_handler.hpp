#ifndef CHORD_DHT_HANDLER_HPP
#define CHORD_DHT_HANDLER_HPP

#include <cmath>
class ChordDhtHandler {
public:
  int avoid_collision_m = 1; // make 0 always 1
  int recorded_arc = 1;
  int avoid_collision_formula = std::pow(2, avoid_collision_m) - 1;
  int recorded_arc_formula = 2 * recorded_arc + 1;
};

#endif // CHORD_DHT_HANDLER_HPP
