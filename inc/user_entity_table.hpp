#ifndef USER_ENTITY_TABLE_HPP
#define USER_ENTITY_TABLE_HPP

#include <cstdio>
#include <cstdlib>

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

class UserData {
public:
  void *source;
  void *destination;
  void *user_data;
  size_t data_size;
};

class DistributesLocator {
  ENodes nodes;
  UserData user_data;
};

#endif // USER_ENTITY_TABLE_HPP
