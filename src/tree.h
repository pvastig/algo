#pragma once

#include <cassert>

namespace Algo {

template <class T>
class Tree {
 public:
  Tree() {
  }
  ~Tree() {
    deleteSubtree(root);
  }

  int height() const {
    return height(root);
  }

  int countNodesLevel(int level) const {
    return countNodesLevel(root, level);
  }

  void add(T const &item) {
    add(root, item);
  }

 private:
  struct Node {
    T item;
    Node *left  = nullptr;
    Node *right = nullptr;

    Node(T i, Node *s = nullptr, Node *b = nullptr)
        : item(i), left(s), right(b) {}
  };
  Node *root = nullptr;

 private:
  void add(Node *&node, T const &item);
  void deleteSubtree(Node *node);
  int height(Node *node) const;
  int countNodesLevel(Node *node, int level) const;
};

template <class T>
void Tree<T>::add(Node *&node, const T &item) {
  if (!node)
    node = new Node(item);
  else if (item < node->item)
    add(node->left, item);
  else
    add(node->right, item);
}

template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
    node = nullptr;
  }
}

template <class T>
int Tree<T>::height(Node *node) const {
  if (!node)
    return 0;
  int max = 0;
  for (auto cur = node->left; cur; cur = cur->right) {
    int curHeght = height(cur);
    if (curHeght > max)
      max = curHeght;
  }
  return max + 1;
}

template <class T>
int Tree<T>::countNodesLevel(Node *node, int level) const {
  if (!node)
    return 0;
  if (level <= 0)
    return 0;
  return countNodesLevel(node->left, level - 1) + (level == 1) +
         countNodesLevel(node->right, level);
}
}  // namespace Algo
