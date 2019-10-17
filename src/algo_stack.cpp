#include "algo_stack.h"

#include <algorithm>
#include <cassert>
#include <sstream>

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

FindMax::FindMax() = default;

void FindMax::push(int value) {
  m_values.push(value);
  if (m_maxValues.empty())
    m_maxValues.push(value);
  else {
    auto top = m_maxValues.top();
    if (value > top)
      m_maxValues.push(value);
    else
      m_maxValues.push(top);
  }
}

void FindMax::pop() {
  m_values.pop();
  m_maxValues.pop();
}

int FindMax::max() const {
  if (!m_maxValues.empty())
    return m_maxValues.top();
  return 0;
}

std::string query(std::string const &str, FindMax &s) {
  if (str == "max")
    return std::to_string(s.max());
  if (str == "pop") {
    s.pop();
    return "";
  }
  if (str.find_first_of("push") != std::string::npos) {
    std::stringstream is(str);
    std::string op;
    is >> op;
    int value = 0;
    is >> value;
    s.push(value);
  }
  return "";
}
}  // namespace Algo
