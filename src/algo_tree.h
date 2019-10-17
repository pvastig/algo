#pragma once

#include <stack>
#include <string>
#include <vector>

namespace Algo {

namespace old {
/* Calculates height of tree. Tree is represented by array. Works at N^2
 * param v array of tree
 * return height
 */
size_t getHeight(std::vector<int> const& v);

void printTree(std::vector<int> const& v);
}  // namespace old

size_t getHeight(std::vector<int> const& v);

}  // namespace Algo
