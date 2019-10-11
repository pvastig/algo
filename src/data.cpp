#include "data.h"

#include <cassert>
#include <iostream>
#include <stack>

using namespace std;
namespace Algo {
size_t checkBraces(std::string const &str) {
  struct BracePos {
    size_t pos;
    char ch;
  };
  std::stack<BracePos> openedBraces;
  size_t pos = 0;
  for (auto ch : str) {
    ++pos;
    if (ch == '(' || ch == '[' || ch == '{') {
      openedBraces.push({pos, ch});
    } else if (ch == ')' || ch == ']' || ch == '}') {
      if (openedBraces.empty())
        return pos;
      auto top = openedBraces.top();
      if ((top.ch == '(' && ch == ')') || (top.ch == '[' && ch == ']') ||
          (top.ch == '{' && ch == '}'))
        openedBraces.pop();
      else
        return pos;
    }
  }

  return openedBraces.empty() ? 0 : openedBraces.top().pos;
}
}  // namespace Algo
