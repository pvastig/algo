#include "../src/algo_stack.h"
#include "../src/algo_tree.h"

#include <gtest/gtest.h>

TEST(Stack, CheckBraces) {
  using namespace Algo;
  ASSERT_EQ(checkBraces("]]]"), 1);
  ASSERT_EQ(checkBraces("{"), 1);
  ASSERT_EQ(checkBraces("]["), 1);
  ASSERT_EQ(checkBraces("()"), 0);
  ASSERT_EQ(checkBraces("(abc"), 1);
  ASSERT_EQ(checkBraces("(a(bc"), 3);
  ASSERT_EQ(checkBraces("[(a)]"), 0);
  ASSERT_EQ(checkBraces("[(a)](((()))"), 6);
  ASSERT_EQ(checkBraces("()[]}"), 5);
  ASSERT_EQ(checkBraces("()()([}"), 7);
  ASSERT_EQ(checkBraces("{{[()]]"), 7);
  ASSERT_EQ(checkBraces("[]([]"), 3);
  ASSERT_EQ(checkBraces("([)]"), 3);
  ASSERT_EQ(checkBraces("(slkj{lk[lsj]}"), 1);
}

TEST(Stack, MaxResult) {
  using namespace Algo;
  {
    FindMax s;
    s.push(7);
    s.push(1);
    s.push(7);
    s.max();
    ASSERT_EQ(s.max(), 7);
    s.pop();
    ASSERT_EQ(s.max(), 7);
  }
  {
    FindMax s;
    s.push(1);
    s.push(2);
    ASSERT_EQ(s.max(), 2);
    s.pop();
    ASSERT_EQ(s.max(), 1);
  }
  {
    FindMax s;
    s.push(2);
    s.push(1);
    ASSERT_EQ(s.max(), 2);
    s.pop();
    ASSERT_EQ(s.max(), 2);
  }
  {
    FindMax s;
    ASSERT_EQ(query("max", s), "0");
  }
  {
    FindMax s;
    ASSERT_EQ(query("max", s), "0");
  }
  {
    FindMax s;
    ASSERT_EQ(query("push 1", s), "");
    ASSERT_EQ(query("push 2", s), "");
    ASSERT_EQ(query("max", s), "2");
    ASSERT_EQ(query("pop", s), "");
    ASSERT_EQ(query("max", s), "1");
  }
  {
    FindMax s;
    ASSERT_EQ(query("push 1", s), "");
    ASSERT_EQ(query("push 2", s), "");
    ASSERT_EQ(query("max", s), "2");
    ASSERT_EQ(query("pop", s), "");
    ASSERT_EQ(query("max", s), "1");
  }
}

TEST(Tree, FindHeightTree) {
  using namespace Algo;
  ASSERT_EQ(old::getHeight({9, 7, 5, 5, 2, 9, 9, 9, 2, -1}), 4);
  ASSERT_EQ(getHeight({9, 7, 5, 5, 2, 9, 9, 9, 2, -1}), 4);
}
