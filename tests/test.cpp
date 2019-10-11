#include "test.h"

#include "../src/data.h"

#include <gtest/gtest.h>

TEST(CheckBraces, PositionResulut) {
  ASSERT_EQ(Algo::checkBraces("]]]"), 1);
  ASSERT_EQ(Algo::checkBraces("{"), 1);
  ASSERT_EQ(Algo::checkBraces("]["), 1);
  ASSERT_EQ(Algo::checkBraces("()"), 0);
  ASSERT_EQ(Algo::checkBraces("(abc"), 1);
  ASSERT_EQ(Algo::checkBraces("(a(bc"), 3);
  ASSERT_EQ(Algo::checkBraces("[(a)]"), 0);
  ASSERT_EQ(Algo::checkBraces("[(a)](((()))"), 6);
  ASSERT_EQ(Algo::checkBraces("()[]}"), 5);
  ASSERT_EQ(Algo::checkBraces("()()([}"), 7);
  ASSERT_EQ(Algo::checkBraces("{{[()]]"), 7);
  ASSERT_EQ(Algo::checkBraces("[]([]"), 3);
  ASSERT_EQ(Algo::checkBraces("([)]"), 3);
  ASSERT_EQ(Algo::checkBraces("(slkj{lk[lsj]}"), 1);
}
