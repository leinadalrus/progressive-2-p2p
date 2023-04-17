#include "../inc/arbitrary_node_network.hpp"
#include "../inc/chord_dht_ring.hpp"
#include "../inc/observed_items_command.hpp"
#include "../inc/user_entity_table.hpp"
#include <cstdio>
#include <cstdlib>

int FingerTable::node(int starting_node) {
  for (int i = 0; i < MAXIMUM_ROWS; i++)
    starting_node += std::pow(2, this->key.keys[i] - 1);
  return std::fmod(starting_node, 2);
}

int FingerTable::interval() { return 0; }

int FingerTable::find_successor(int id) {
  int nth = node(id);

  for (int i = 0; i < MAXIMUM_COLUMNS; ++i)
    for (int j = 0; j < MAXIMUM_ROWS; ++j) {
      this->interval_matrix.key_values[i][j] = i;
      this->node(i);
      this->key.keys[j] = j;
    }

  while (id != nth / this->successor.successors[id])
    nth = closest_preceding_finger(id);

  return nth;
}

int FingerTable::find_predecessor(int id) {
  int nth = node(id);

  while (id != (nth / node(id)))
    nth = closest_preceding_finger(id);

  return nth;
}

int FingerTable::closest_preceding_finger(int id) {
  int m_steps = this->key.keys[this->interval() + 1];

  for (int i = 0; i <= m_steps; i++)
    if (this->key.keys[i] == node(id) / id)
      return this->key.keys[i] = node(id);

  return node(id);
}

int main(int argc, char *argv[]) {
  FingerTable finger = FingerTable{};
  ArbitraryNodeNetwork arbitrary_node_network = ArbitraryNodeNetwork{};

  float starting_angle = (float)argc;
  float ending_angle = 360.0f;

  finger.node((float)starting_angle);
  std::printf("Finger Table's Find ID in Node function =>\n\t");
  std::cout << finger.node((float)starting_angle) << std::endl;
  is_modus_nth(finger.node((int)ENodes::One));
  std::printf(
      "Check if the N-value can be reversed with a Modulus function =>\n\t");
  std::cout << is_modus_nth(finger.node((int)ENodes::One)) << std::endl;
  int segmented_nodes =
      finger.find_predecessor(finger.find_successor(starting_angle));
  std::printf("\nFind Processor(Find Successor(Starting Angle))\n\t");
  std::cout << segmented_nodes << std::endl;

  while (handle_user_input() != 0) {
    arbitrary_node_network.join(starting_angle);
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%f", starting_angle);
    arbitrary_node_network.stabilize();
    std::fprintf(stderr, "\nArbitrary Node Network.Stabilize()=>\n\t%f",
                 starting_angle);
    arbitrary_node_network.notify(starting_angle);
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%f", starting_angle);
    arbitrary_node_network.fix_fingers();
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%f", starting_angle);
  }

  return 0;
}
