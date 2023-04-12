#ifndef FINGER_TABLE_HPP
#define FINGER_TABLE_HPP

#include <iostream>
#include <cmath>

#ifdef M_PI
#define M_PI (3.14)
#endif // M_PI

#define MAXIMUM_COLUMNS (10)
#define MAXIMUM_ROWS (10)

class StartingNode
{
public:
  int nodes[8];
};

class IntervalMatrix
{
public:
  int key_values[8][8];
};

class Successor
{
public:
  int successors[8];
};

class Key
{
public:
  int keys[8];
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