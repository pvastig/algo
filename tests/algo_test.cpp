#include "../src/algo.h"

#include <gtest/gtest.h>

TEST(Algo, checkCountMatchedSymbols) {
  using namespace Algo;
  ASSERT_EQ(countMatchedSymbols({"aabbccd"}, "ab"), 4);
  ASSERT_EQ(countMatchedSymbols("ab", {"aabbccd"}),
            2);  // thinking about searching long pattern in short string
  ASSERT_EQ(countMatchedSymbols("aabbccd", {"aabbccd"}), 7);
  ASSERT_EQ(countMatchedSymbols({""}, {""}), 0);
  ASSERT_EQ(countMatchedSymbols({"a"}, {""}), 0);
  ASSERT_EQ(countMatchedSymbols({""}, {"a"}), 0);
  ASSERT_EQ(countMatchedSymbols({"aaaa"}, {"a"}), 4);
  ASSERT_EQ(countMatchedSymbols({"AaaB"}, {"a"}), 2);
  ASSERT_EQ(countMatchedSymbols({"A1aaB2"}, {"12"}), 2);
}

TEST(Algo, checkCountOnes) {
  using namespace Algo;
  ASSERT_EQ(countOnes({0, 0, 0, 0, 0, 0, 0}), 0);
  ASSERT_EQ(countOnes({1, 0, 0, 0, 0, 0, 0}), 1);
  ASSERT_EQ(countOnes({0, 0, 0, 0, 0, 0, 1}), 1);
  ASSERT_EQ(countOnes({0, 0, 0, 0, 1, 1, 1}), 3);
  ASSERT_EQ(countOnes({1, 1, 1, 0, 0, 0, 0}), 3);
  ASSERT_EQ(countOnes({1, 1, 1, 0, 0, 0, 1}), 3);
  ASSERT_EQ(countOnes({1, 1, 1, 0, 1, 0, 1}), 3);
  ASSERT_EQ(countOnes({1, 1, 1, 0, 0, 1, 1}), 3);
  ASSERT_EQ(countOnes({0, 1, 1, 0, 1, 1, 1}), 3);
  ASSERT_EQ(countOnes({0, 1, 1, 0, 1, 1, 0}), 2);
  ASSERT_EQ(countOnes({1, 0, 1, 0, 1, 0, 1}), 1);
  ASSERT_EQ(countOnes({0, 1, 0, 1, 0, 1, 0}), 1);
  ASSERT_EQ(countOnes({1, 1, 1, 1, 1, 1, 1}), 7);
  ASSERT_EQ(countOnes({}), 0);
  ASSERT_EQ(countOnes({1, 2, 3, 4, 5, 6, 7}), 1);
  ASSERT_EQ(countOnes({5, 5, 5, 5, 5, 1}), 1);
  ASSERT_EQ(countOnes({5, 5, 5, 5, 5, 1}, 5), 5);
  ASSERT_EQ(countOnes({5, 5, 5, 5, 5, 1}, 2), 0);
  ASSERT_EQ(countOnes({2, 5, 2, 2, 2, 1}, 5), 1);
  ASSERT_EQ(countOnes({100, 5, 100, 100, 2, 100}, 100), 2);
}
