#include "test.h"

#include "../src/data.h"

#include <cassert>
#include <iostream>

void Test::braces() {
  using namespace Algo;
  {
    std::string str = "]]]";
    assert(checkBraces(str) == 1);
  }
  {
    std::string str = "{";
    assert(checkBraces(str) == 1);
  }
  {
    std::string str = "][";
    assert(checkBraces(str) == 1);
  }
  {
    std::string str = "()";
    assert(checkBraces(str) == 0);
  }
  {
    std::string str = "(abc";
    assert(checkBraces(str) == 1);
  }
  {
    std::string str = "[(a)]";
    assert(checkBraces(str) == 0);
  }
  {
    std::string str = "[(a)](((()))";
    assert(checkBraces(str) == 6);
  }
  {
    std::string str = "()[]}";
    assert(checkBraces(str) == 5);
  }
  {
    std::string str = "()()([}";
    assert(checkBraces(str) == 7);
  }
  {
    std::string str = "{{[()]]";
    assert(checkBraces(str) == 7);
  }
  {
    std::string str = "[]([]";
    assert(checkBraces(str) == 3);
  }
  {
    std::string str = "([)]";
    assert(checkBraces(str) == 3);
  }
  {
    std::string str = "(slkj{lk[lsj]}";
    assert(checkBraces(str) == 1);
  }
}
