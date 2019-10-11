#include "../src/data.h"

#include <gtest/gtest.h>

TEST(CheckBraces, PositionResulut) {
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
