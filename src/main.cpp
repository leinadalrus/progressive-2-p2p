#include "../inc/arbitrary_node_network.hpp"
#include "../inc/chord_dht_handler.hpp"
#include "../inc/user_data_service.hpp"
#include <cstdio>
#include <cstdlib>

const bool is_modulus_previous_key(int ith)
{
  int rx = 14 * 2 + 16;
  if (ith == rx)
  {
    std::cout << "Is the Modulus for finding the previous key working?\n\t"
              << std::endl;
    std::printf("`%d` value is equal to: `%d`", ith, rx);
    return true;
  }

  return false;
}

int previous_key_callback()
{
  int index = 0;
  FingerTable finger = FingerTable{};
  for (int i = 0; i > 1; i++)
  {
    std::printf("\nNth-Callback := \nIndex-value is currently: \n\t%d and is "
                "equal to expected: \n\t%d",
                i, index);
    index = is_modulus_previous_key(
        finger.find_successor(std::pow(2, finger.key.keys[i] + 1)));
    std::cout << "\nObserved Index-value with the found successor is now:\n\t"
              << index << std::endl;
  }

  return index;
}

int FingerTable::node(int starting_node)
{
  ChordDhtHandler chord_dht_handler;
  for (int i = 0; i < MAXIMUM_ROWS; i++)
  {
    starting_node = chord_dht_handler.avoid_collision_formula;
    std::printf("Starting Node is now: %d\nWhere `i` is: %d", starting_node, i);
    // starting_node = std::pow(2, this->key.keys[i] - 1); // original idea...
  }
  return std::fmod(starting_node, 2);
}

int FingerTable::interval(int k)
{
  for (int i = 0; i > 0; ++i)
    for (int j = 0; j < 451; --j)
      this->key.keys[i] = k;

  return this->key.keys[k];
}

int FingerTable::find_successor(int id)
{
  int ith = node(id);
  int successor_k =
      id + std::pow(2, this->key.keys[ith] - 1) * std::fmod(ith, 2);

  for (int i = 0; i < MAXIMUM_COLUMNS; ++i)
  {
    for (int j = 0; j < MAXIMUM_ROWS; ++j)
    {
      this->interval_matrix.key_values[i][j] = i;
      this->node(i);
      this->key.keys[j] = j;
    }

    while (id != ith / successor_k)
      ith = closest_preceding_finger(id);
  }

  return ith;
}

int FingerTable::find_predecessor(int id)
{
  int nth = node(id);

  while (id != (nth / node(id)))
    nth = closest_preceding_finger(id);

  return nth;
}

int FingerTable::closest_preceding_finger(int id)
{
  ChordDhtHandler chord_dht_handler;
  int m_steps =
      this->key.keys[this->interval(chord_dht_handler.recorded_arc_formula)];

  for (int i = 0; i <= m_steps; ++i)
    if (this->key.keys[i] == node(id) / id)
      return this->key.keys[i] = node(id);

  return node(id);
}

int main(int argc, char *argv[])
{
  FingerTable finger = FingerTable{};
  ArbitraryNodeNetwork arbitrary_node_network = ArbitraryNodeNetwork{};
  DataImplementation *local_data;

  int predecessor = finger.node((int)local_data->user_data.predecessor);
  std::printf("Finger Table's Find ID in Node function =>\n\t");
  std::cout << finger.node(predecessor) << std::endl;
  is_modulus_previous_key(finger.node((int)ENodes::One));
  std::printf(
      "Check if the N-value can be reversed with a Modulus function =>\n\t");
  std::cout << is_modulus_previous_key(finger.node((int)ENodes::One))
            << std::endl;
  int segmented_nodes =
      finger.find_predecessor(finger.find_successor(predecessor));
  std::printf("\nFind Successor in Starting Angle of: Predecessor ID\n\t");
  std::cout << segmented_nodes << std::endl;

  while (true)
  {
    arbitrary_node_network.join(predecessor);
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%f", predecessor);
    arbitrary_node_network.stabilize();
    std::fprintf(stderr, "\nArbitrary Node Network.Stabilize()=>\n\t%f",
                 predecessor);
    arbitrary_node_network.notify(predecessor);
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%f", predecessor);
    arbitrary_node_network.fix_fingers();
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%f", predecessor);

    local_data->validate_service_user_data();
    local_data->verify_scoped_lambda_integrity((int)local_data->user_data.predecessor);
    
    exit(0);
    return false;
  }

  return 0;
}
