#include "../src/algo.h"

#include <gtest/gtest.h>

TEST(Algo, CheckCountMatchedSymbols) {
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
