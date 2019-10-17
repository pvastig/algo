#include "algo_stack.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>

namespace Algo {

void printIndex(int value, std::vector<int> const &v) {
  std::stack<size_t> idx;
  for (size_t i = 0; i < v.size(); ++i)
    if (value == v[i]) {
      idx.push(i);
    }

  if (idx.empty())
    return;

  while (!idx.empty()) {
    std::cout << idx.top() << ' ';
    printIndex(idx.top(), v);
    idx.pop();
  }
}

size_t height(int value, std::vector<int> const &v) {
  std::stack<size_t> idx;
  for (size_t i = 0; i < v.size(); ++i)
    if (value == v[i]) {
      idx.push(i);
    }

  if (idx.empty())
    return 0;

  size_t heigth = 1;
  while (!idx.empty()) {
    heigth = std::max(heigth, 1 + height(idx.top(), v));
    idx.pop();
  }
  return heigth;
}

namespace old {
size_t getHeight(std::vector<int> const &v) {
  return height(-1, v);
}

void printTree(std::vector<int> const &v) {
  printIndex(-1, v);
}
}  // namespace old

void fillDepth(std::vector<int> const &parent, size_t i,
               std::vector<size_t> &depth) {
  if (depth[i])
    return;

  if (parent[i] == -1) {
    depth[i] = 1;
    return;
  }

  if (depth[parent[i]] == 0)
    fillDepth(parent, parent[i], depth);

  depth[i] = depth[parent[i]] + 1;
}

size_t getHeight(const std::vector<int> &v) {
  auto n = v.size();
  std::vector<size_t> depth(n, 0);

  for (size_t i = 0; i < n; ++i)
    fillDepth(v, i, depth);

  if (auto heigth = std::max_element(depth.begin(), depth.end());
      heigth != depth.end())
    return *heigth;
  return 0;
}
}  // namespace Algo
