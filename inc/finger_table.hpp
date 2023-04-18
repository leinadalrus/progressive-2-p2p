#ifndef FINGER_TABLE_HPP
#define FINGER_TABLE_HPP

#include <cmath>
#include <iostream>

#define _USE_MATH_DEFINES
#define MINIMUM_SEGMENTED_NODES (10)
#define MAXIMUM_COLUMNS (2)
#define MAXIMUM_ROWS (10)

enum class ENodes {
  One = 0,
  Two = 85,
  Three = 133,
  Four = 182,
  Five = 210,
  Six = 245,
  Seven = 279,
  Eight = 324,
  Nine = 395,
  Zero = 451,
};

class StartingNode {
public:
  int nodes[MAXIMUM_ROWS];
};

class IntervalMatrix {
public:
  int key_values[MAXIMUM_COLUMNS][MAXIMUM_ROWS];
};

class Successor {
public:
  int successors[MAXIMUM_ROWS];
};

class Key {
public:
  int keys[MAXIMUM_ROWS];
};

class FingerTable {
public:
  StartingNode starting_node;
  IntervalMatrix interval_matrix;
  Successor successor;
  Key key;

  int node(int starting_node);
  int interval(int k);
  int find_successor(int id);
  int find_predecessor(int id);
  int closest_preceding_finger(int id);
};

const bool is_modulus_previous_key(int ith);

int previous_key_callback();

#endif // FINGER_TABLE_HPP
