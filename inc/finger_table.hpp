#ifndef FINGER_TABLE_HPP
#define FINGER_TABLE_HPP

#include <iostream>

const int MaxmimumLength = 10;
const int MaximumColumns = 2;
const int MaximumRows = 10;

class IntervalMatrix
{
public:
  int key_values[MaximumColumns][MaximumRows];
};

class Key
{
public:
  int keys[MaximumRows];
};

class FingerTable
{
public:
  IntervalMatrix interval_matrix;
  DataImplementation impl;
  ChordDht chord;
  Key key;

  int starting_node(int node);
  int interval(int k);
  int find_successor(int id);
  int find_predecessor(int id);
  int closest_preceding_finger(int id);
};

const bool is_modulus_previous_key(int ith);

int previous_key_callback();

#endif // FINGER_TABLE_HPP
