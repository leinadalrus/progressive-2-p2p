#ifndef ARBITRARY_NODE_NETWORK_HPP
#define ARBITRARY_NODE_NETWORK_HPP

#include "chord_dht.hpp"
#include "finger_table.hpp"

class ArbitraryNodeNetwork
{
  FingerTable finger;
  ChordDht chord;

public:
  void
  join(int node)
  {
    this->finger.find_predecessor(this->chord.recorded_arc_formula(finger.impl.data.predecessor));
    finger.impl.data.predecessor = NULL;

    finger.find_successor(finger.impl.data.predecessor);
  };

  void update_finger_table(int successor, int predecessor)
  {
    int node = this->finger.starting_node(successor);
    int interval = this->finger.key
                       .keys[this->finger.starting_node(predecessor)];

    if (successor == node / interval)
      while (predecessor != node - 1 && node >= 1)
        this->finger.key.keys[predecessor] = successor;
  }

  void notify(int n1)
  {
    if (finger.impl.data.predecessor == 0 || n1 > finger.impl.data.predecessor && n1 < finger.starting_node(finger.impl.data.predecessor))
      finger.impl.data.predecessor = n1;
  }

  void stabilize()
  {
    FingerTable finger = FingerTable{};
    int x = finger.impl.data.predecessor;
    if (x > finger.impl.data.predecessor && x < finger.impl.data.successor)
      finger.impl.data.successor = x;

    notify(finger.impl.data.predecessor);
  }

  void fix_fingers()
  {
    int next = next + 1;
    if (next > chord.avoid_collision_formula(1))
      next = 1;
    finger.key.keys[next];
  }

  void check_predecessor()
  {
    if (finger.impl.data.predecessor == NULL)
      finger.impl.data.predecessor = 0;
  }
};

#endif // ARBITRARY_NODE_NETWORK_HPP
