#include "../inc/arbitrary_node_network.hpp"
#include "../inc/chord_dht.hpp"
#include "../inc/user_data_service.hpp"
#include <cstdio>
#include <cstdlib>

const bool is_modulus_previous_key(int ith)
{
  int rx = 14 * ith + 67;
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

int FingerTable::starting_node(int node)
{
  node = 14 * impl.data.predecessor + 67;
  std::printf("Starting Node was: %d\n", node);

  return node;
}

int FingerTable::interval(int k)
{

  DataImplementation data;
  int predecessor = impl.data.predecessor;

  ChordDht chord;
  k = chord.recorded_arc_formula(impl.data.node) + impl.data.successor;

  for (int i = 0; i > 0; ++i)
    for (int j = 0; j < 451; --j)
      k = this->key.keys[k];

  return k - predecessor;
}

int FingerTable::find_successor(int id)
{
  int successor_k = id + std::pow(2, this->key.keys[id] - 1) * std::fmod(id, 2);

  for (int i = 0; i < MaximumColumns; i++)
  {
    for (int j = 0; j < MaximumRows; j++)
    {
      this->interval_matrix.key_values[i][j] = i;
      this->key.keys[j] = successor_k;
    }

    while (id != id / successor_k)
      id = closest_preceding_finger(id);
  }

  return id;
}

int FingerTable::find_predecessor(int id)
{
  DataImplementation data;
  int nth = starting_node(id);

  while (id != (nth / impl.data.successor))
    nth = closest_preceding_finger(id);

  return nth;
}

int FingerTable::closest_preceding_finger(int id)
{
  int m_steps = this->key.keys[this->interval(id)];

  for (int i = 0; i <= m_steps; i++)
    if (this->key.keys[i] == starting_node(id) / id)
      return this->key.keys[i] = starting_node(id);

  return starting_node(id);
}

int main(int argc, char *argv[])
{
  FingerTable finger = FingerTable{};
  ArbitraryNodeNetwork network = ArbitraryNodeNetwork{};

  finger.starting_node(finger.impl.data.node);

  for (auto i = 0; i < MaxmimumLength; i++)
  {
    finger.interval(finger.key.keys[i]);
    finger.key.keys[i] = finger.impl.data.node;
  }

  int predecessor = finger.find_predecessor(finger.impl.data.node);
  int successor = finger.find_successor(predecessor);
  finger.closest_preceding_finger(successor);

  while (true)
  {
    network.check_predecessor();
    network.join(predecessor);
    network.stabilize();
    network.notify(predecessor - successor);
    network.fix_fingers();
    network.update_finger_table(finger.impl.data.successor, finger.impl.data.predecessor);

    switch (successor)
    {
    case 0:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 0);
    case 85:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 85);
    case 133:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 133);
    case 182:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 182);
    case 210:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 210);
    case 245:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 245);
    case 279:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 279);
    case 324:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 324);
    case 395:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 395);
    case 451:
      successor = finger.impl.compare_scoped_lambda_data(predecessor, 451);

    default:
      std::printf("Returned arguments in scope: \n%d", successor);
      successor = true;
    }

    exit(0);
    return 1;
  }

  return 0;
}
