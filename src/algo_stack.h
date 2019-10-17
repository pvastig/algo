#pragma once

#include <stack>
#include <string>

namespace Algo {
/*
 * The metod finds not closed or opened brace in the string
 * param str input string
 * return position of not closed or opened brace
 */
size_t checkBraces(std::string const& str);

class FindMax {
 public:
  FindMax();
  void push(int value);
  void pop();
  int max() const;

 private:
  std::stack<int> m_values;
  std::stack<int> m_maxValues;
};

std::string query(std::string const& str, FindMax& s);

}  // namespace Algo
