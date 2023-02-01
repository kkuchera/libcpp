#include <string>

#include "gtest/gtest.h"
#include "lru_cache.hpp"

TEST(LruCacheTest, TestDefaultConstruction) {
  auto x = lru_cache<int, std::string>{};
  ASSERT_EQ(x.size(), 0);
  ASSERT_EQ(x.capacity(), 0);
  ASSERT_TRUE(x.empty());
}

TEST(LruCacheTest, TestConversions) {
  auto x = lru_cache<int, std::string>{3};
  ASSERT_EQ(x.size(), 0);
  ASSERT_EQ(x.capacity(), 3);
  ASSERT_TRUE(x.empty());

  const auto l = {std::pair<const int, std::string>{0, "hello"}, {2, "world"}};
  auto y = lru_cache<int, std::string>{l};
  ASSERT_EQ(y.size(), 2);
  ASSERT_EQ(y.capacity(), 2);
  ASSERT_FALSE(y.empty());
  ASSERT_TRUE(std::equal(y.rbegin(), y.rend(), l.begin()));
}

TEST(LruCacheTest, TestFind) {
  auto x = lru_cache<int, std::string>{{0, "hello"}, {2, "world"}};
  ASSERT_EQ(x.begin()->first, 2);
  ASSERT_EQ(x.begin()->second, "world");
  const auto it = x.find(0);
  ASSERT_EQ(it->first, 0);
  ASSERT_EQ(it->second, "hello");
}

TEST(LruCacheTest, TestInsertExisting) {
  auto x = lru_cache<int, std::string>{{0, "hello"}, {2, "world"}};
  ASSERT_EQ(x.begin()->first, 2);
  ASSERT_EQ(x.begin()->second, "world");
  ASSERT_EQ(x.size(), 2);
  auto [it, b] = x.insert({0, "foo"});
  ASSERT_EQ(x.begin()->first, 0);
  ASSERT_EQ(x.begin()->second, "foo");
  ASSERT_EQ(x.size(), 2);
  ASSERT_FALSE(b);
  ASSERT_EQ(it->first, 0);
  ASSERT_EQ(it->second, "foo");
  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "world");
}

TEST(LruCacheTest, TestInsertNew) {
  auto x = lru_cache<int, std::string>{{0, "hello"}, {2, "world"}};
  ASSERT_EQ(x.begin()->first, 2);
  ASSERT_EQ(x.begin()->second, "world");
  ASSERT_EQ(x.size(), 2);
  auto [it, b] = x.insert({1, "foo"});
  ASSERT_EQ(x.begin()->first, 1);
  ASSERT_EQ(x.begin()->second, "foo");
  ASSERT_EQ(x.size(), 2);
  ASSERT_TRUE(b);
  ASSERT_EQ(it->first, 1);
  ASSERT_EQ(it->second, "foo");
  ++it;
  ASSERT_EQ(it->first, 2);
  ASSERT_EQ(it->second, "world");
}

TEST(LruCacheTest, TestAccess) {
  const auto l = {std::pair<const int, std::string>{0, "hello"}, {2, "world"}};
  auto x = lru_cache<int, std::string>{l};
  ASSERT_TRUE(std::equal(x.rbegin(), x.rend(), l.begin()));
  ASSERT_EQ(x[0], "hello");
  ASSERT_TRUE(std::equal(x.begin(), x.end(), l.begin()));
  ASSERT_EQ(x.at(2), "world");
  ASSERT_TRUE(std::equal(x.begin(), x.end(), l.begin()));
  ASSERT_EQ(x[7], "");
}

TEST(LruCacheTest, PopFront) {
  auto x = lru_cache<int, std::string>{{0, "hello"}, {2, "world"}};
  ASSERT_EQ(x.begin()->first, 2);
  ASSERT_EQ(x.begin()->second, "world");
  x.pop_front();
  ASSERT_EQ(x.begin()->first, 0);
  ASSERT_EQ(x.begin()->second, "hello");
  ASSERT_EQ(x.size(), 1);
  ASSERT_EQ(x.capacity(), 2);
  x.shrink_to_fit();
  ASSERT_EQ(x.capacity(), 1);
}

TEST(LruCacheTest, PopBack) {
  auto x = lru_cache<int, std::string>{{0, "hello"}, {2, "world"}};
  ASSERT_EQ(x.begin()->first, 2);
  ASSERT_EQ(x.begin()->second, "world");
  x.pop_back();
  ASSERT_EQ(x.begin()->first, 2);
  ASSERT_EQ(x.begin()->second, "world");
  ASSERT_EQ(x.size(), 1);
  ASSERT_EQ(x.capacity(), 2);
}
