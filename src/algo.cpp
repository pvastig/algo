#include "algo.h"

#include <cassert>
#include <iostream>
#include <set>

namespace Algo {

int countMatchedSymbols(std::string const& str, std::string const& pattern) {
  int countChar[255] = {};
  for (auto const ch : pattern) {
    int charCode = static_cast<int>(ch);
    if (!countChar[charCode])
      ++countChar[static_cast<int>(ch)];
  }
  int result = 0;
  for (auto const ch : str)
    result += countChar[static_cast<int>(ch)];
  return result;
}

int countOnes(std::vector<int> const& v, int value) {
  int countMax = 0;
  int countOne = 0;
  for (auto const item : v) {
    if (item == value)
      ++countOne;
    else {
      countMax = std::max(countMax, countOne);
      countOne = 0;
    }
  }
  return std::max(countMax, countOne);
}
bool deleteValues(std::vector<int>& v, int value) {
  size_t const beforeDeleting = v.size();
  auto n                = v.begin();
  for (; n != v.end(); ++n) {
    if (*n == value)
      break;
  }

  if (n == v.end())
    return false;

  for (auto it = n; ++it != v.end();) {
    if (!(*it == value))
      *n++ = std::move(*it);
  }
  assert(n != v.end());
  v.erase(n, v.end());
  size_t const afterDeleting = v.size();
  return beforeDeleting != afterDeleting;
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
  return s;
}

std::string generateBraces(int pairs, char openedBr, char closedBr) {
  return generate("", 0, 0, pairs);
}

bool checkAnagrams(const std::string& str) {
  std::set<char> s;
  for (auto const ch : str)
    if (bool notInserted = !s.insert(ch).second)
      return false;
  return true;
}

std::vector<int> mergeArrays(const std::vector<std::vector<int> >& v) {
  size_t elements = 0;
  for (auto const& item : v)
    elements += item.size();
  std::vector<int> result;
  std::vector<int> res;
  std::vector<size_t> index(v.size(), 0);
  for (size_t j = 0; j < elements; ++j) {
    bool minValueFound = false;
    int foundIndex     = -1;
    auto& first        = v[0];
    int minValue       = first[index[0]];
    for (size_t i = 0; i < v.size(); ++i) {
      if (index[i] >= v[i].size())
        continue;
      auto& vec = v[i];
      std::cout << "first: " << vec[index[i]] << "\n";
      if (vec[index[i]] < minValue) {
        minValue      = vec[index[i]];
        minValueFound = true;
        foundIndex    = i;
      }
    }
    if (index[0] >= v[0].size())
      continue;

    if (foundIndex < 0) {
      auto& vec = *v.begin();
      minValue  = vec[index[0]];
      ++index[0];
    } else if (foundIndex >= 0) {
      auto& vec = v[foundIndex];
      minValue  = vec[index[foundIndex]];
      ++index[foundIndex];
    }
    std::cout << "minValue = " << minValue << "\n";
    result.push_back(minValue);
  }
}

}  // namespace Algo
