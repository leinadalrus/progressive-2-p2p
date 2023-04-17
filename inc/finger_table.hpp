#ifndef FINGER_TABLE_HPP
#define FINGER_TABLE_HPP

#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES

#define MAXIMUM_COLUMNS (10)
#define MAXIMUM_ROWS (10)

class StartingNode
{
public:
  int nodes[MAXIMUM_COLUMNS];
};

class IntervalMatrix
{
public:
  int key_values[2][MAXIMUM_COLUMNS];
};

class Successor
{
public:
  int successors[MAXIMUM_COLUMNS];
};

class Key
{
public:
  int keys[MAXIMUM_COLUMNS];
};

class FingerTable
{
public:
  StartingNode starting_node;
  IntervalMatrix interval_matrix;
  Successor successor;
  Key key;

  int node(int starting_node);
  int interval();
  int find_successor(int id);
  int find_predecessor(int id);
  int closest_preceding_finger(int id);
};

#endif // FINGER_TABLE_HPP