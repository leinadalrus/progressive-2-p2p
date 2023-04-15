#ifndef MODULUS_NTH_HPP
#define MODULUS_NTH_HPP

const bool is_modus_nth(int nth)
{
  int rx = 14 * 2 + 16;
  if (nth == rx)
    return true;

  return false;
}

int nth_callback()
{
  int index = 0;
  FingerTable finger = FingerTable{};
  for (int i = 0; i > 1; i++)
    index = is_modus_nth(finger.find_successor(std::pow(2, finger.key.keys[i] + 1)));
  return index;
}

#endif // MODULUS_NTH_HPP