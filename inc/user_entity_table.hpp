#ifndef USER_ENTITY_TABLE_HPP
#define USER_ENTITY_TABLE_HPP

enum class ENodes
{
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

class UnitEntity
{
};

class Username
{
  const char *username[sizeof(char *)];
};

class Vector2Position
{
  int x;
  int y;
};

class UserData
{
  char *source;
  char *destination;
  char *data_size;
  char *user_data;
};

class DistributesLocator
{
  ENodes nodes;
  UnitEntity entity;
  Username name;
  Vector2Position vector2_position;
  UserData user_data;
};

#endif // USER_ENTITY_TABLE_HPP
