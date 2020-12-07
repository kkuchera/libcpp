#include "kway_merge.hpp"

#include <algorithm>
#include <deque>
#include <list>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

struct range {
  template <typename T> auto operator()(T &x) {
    return std::make_pair(x.begin(), x.end());
  }
};

TEST(KwayMergeTest, TestVectorVectorAscending) {
  auto v = std::vector<std::vector<int>>{{1, 4, 7}, {2, 3, 6, 8}, {0, 5, 9}};
  using it = decltype(v)::value_type::iterator;

  auto ranges = std::vector<std::pair<it, it>>{};
  std::transform(v.begin(), v.end(), std::back_inserter(ranges), range{});

  auto merged = std::vector<int>{};
  kway_merge(ranges.begin(), ranges.end(), std::back_inserter(merged));

  const auto exp = std::vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_EQ(merged, exp);
}

TEST(KwayMergeTest, TestDequeListDescending) {
  auto d = std::deque<std::list<int>>{{7, 4, 1}, {8, 6, 3, 2}, {9, 5, 0}};
  using it = decltype(d)::value_type::iterator;

  auto ranges = std::deque<std::pair<it, it>>{};
  std::transform(d.begin(), d.end(), std::back_inserter(ranges), range{});

  auto merged = std::vector<int>{};
  kway_merge(ranges.begin(), ranges.end(), std::back_inserter(merged),
             [](auto &x, auto &y) { return *x.first > *y.first; });

  const auto exp = std::vector{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  ASSERT_EQ(merged, exp);
}

TEST(KwayMergeTest, TestDuplicates) {
  auto d = std::deque<std::list<int>>{{-1}, {0, 0, 1, 1}, {-2, -1, 0}};
  using it = decltype(d)::value_type::iterator;

  auto ranges = std::deque<std::pair<it, it>>{};
  std::transform(d.begin(), d.end(), std::back_inserter(ranges), range{});

  auto merged = std::vector<int>{};
  kway_merge(ranges.begin(), ranges.end(), std::back_inserter(merged));

  const auto exp = std::vector{-2, -1, -1, 0, 0, 0, 1, 1};
  ASSERT_EQ(merged, exp);
}
