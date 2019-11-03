#include "algo.h"

#include <algorithm>
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

bool checkAnagrams(const std::string& str) {
  std::set<char> s;
  for (auto const ch : str)
    if (bool notInserted = !s.insert(ch).second)
      return false;
  return true;
}

void removeValue(std::vector<int>& v) {
  auto it = v.begin();
  auto n  = v.begin();
  for (; n != v.end(); ++n)
    if (*n != 0)
      break;

  if (n != v.end()) {
  }

  for (; it != v.end(); ++it) {
    if (*it == 0) {
      std::swap(*it, *n);
      while (n != v.end() && *n == 0) {
        n++;
      }
    }
  }

  for (auto it = v.begin(); it != v.end();) {
    if (*it == 0)
      it = v.erase(it++);
    else
      ++it;
  }
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
