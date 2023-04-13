#ifndef ARBITRARY_NODE_NETWORK_HPP
#define ARBITRARY_NODE_NETWORK_HPP

#include "finger_table.hpp"

class ArbitraryNodeNetwork
{
  FingerTable finger_table;

public:
  void join(int node)
  {
    if (node)
      update_others();
    else
    {
      for (int i = 1; i < this->finger_table.interval() + 1; i++)
        this->finger_table.key.keys[i] = node;

      this->finger_table.find_predecessor(node);
    }
  };

  int nullify(int node)
  {
    return node;
  }

  void update_others()
  {
    int m_steps = this->finger_table.key.keys[this->finger_table.interval() + 1];

    for (int i = 0; i < m_steps; i++)
    {
      int predecessor = this->finger_table.find_predecessor(this->finger_table.node(i));
      update_finger_table(this->finger_table.node(i), predecessor);
    }
  }

  void update_finger_table(int successor, int predecessor)
  {
    int node = this->finger_table.node(successor);
    int interval = this->finger_table.key.keys[this->finger_table.node(predecessor)];

    if (successor == node / interval)
      while (predecessor != node - 1 && node >= 1)
        this->finger_table.key.keys[predecessor] = successor;
  }

  void notify(int node)
  {
  }

  void stabilize()
  {
    FingerTable finger_table = FingerTable{};
    notify(finger_table.node(1));
  }

  void fix_fingers()
  {
  }
};

#endif // ARBITRARY_NODE_NETWORK_HPP