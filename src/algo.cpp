#include "algo.h"

#include <algorithm>
#include <iostream>
#include <set>

namespace Algo {

int seachSubStr(std::string const& j, std::string const& s) {
  int countChar[255] = {};
  for (auto const ch : j) {
    int charCode = static_cast<int>(ch);
    if (!countChar[charCode])
      ++countChar[static_cast<int>(ch)];
  }
  int result = 0;
  for (auto const ch : s)
    result += countChar[static_cast<int>(ch)];
  return result;
}

int countOnes(std::vector<int> const& v) {
  int countMax = 0;
  int countOne = 0;
  for (auto const item : v) {
    if (item == 1)
      ++countOne;
    else {
      countMax = std::max(countMax, countOne);
      countOne = 0;
    }
  }
  return std::max(countMax, countOne);
}

void deleteDublicates(const std::vector<int>& v) {
  if (v.empty())
    return;
  std::cout << *v.begin() << '\n';
  int value = *v.begin();
  for (auto it = std::next(v.begin()); it != v.end(); ++it) {
    if (value != *it)
      std::cout << *it << '\n';
    value = *it;
  }
}

std::string generate(std::string s, int l, int r, int pairs) {
  if (l == pairs && r == pairs)
    return s += '\n';
  else {
    if (l < pairs)
      generate(s + '(', l + 1, r, pairs);
    if (r < l)
      generate(s + ')', l, r + 1, pairs);
  }
}

std::string generateBraces(int pairs, char openedBr, char closedBr) {
  generate("", 0, 0, pairs);
}

bool checkAnnagrams(const std::string& str) {
  std::set<char> s;
  for (auto const ch : str)
    if (bool notInserted = !s.insert(ch).second)
      return false;
  return true;
}

}  // namespace Algo
