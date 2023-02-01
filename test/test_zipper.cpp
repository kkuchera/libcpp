#include "zipper.hpp"

#include <deque>
#include <list>
#include <string>
#include <vector>

#include "gtest/gtest.h"

TEST(ZipperTest, TestSize) {
  zipper<std::vector<int>, std::deque<char>, std::list<std::string>> z;
  ASSERT_EQ(z.size(), 0);
  ASSERT_TRUE(z.empty());
  z.push_back(0, 'a', "abc");
  z.push_back(1, 'b', "def");
  z.push_back(2, 'c', "ghi");
  ASSERT_EQ(z.size(), 3);
  ASSERT_FALSE(z.empty());
  z.pop_back();
  ASSERT_EQ(z.size(), 2);
  ASSERT_FALSE(z.empty());
  z.pop_back();
  ASSERT_EQ(z.size(), 1);
  ASSERT_FALSE(z.empty());
  z.pop_back();
  ASSERT_EQ(z.size(), 0);
  ASSERT_TRUE(z.empty());
}

TEST(ZipperTest, TestElements) {
  zipper<std::vector<int>, std::deque<char>, std::list<std::string>> z;
  z.push_back(0, 'a', "abc");
  z.push_back(1, 'b', "def");
  z.push_back(2, 'c', "ghi");
  static constexpr auto e0 = {0, 1, 2};
  static constexpr auto e1 = {'a', 'b', 'c'};
  static constexpr auto e2 = {"abc", "def", "ghi"};
  ASSERT_TRUE(std::equal(get<0>(z).first, get<0>(z).second, e0.begin()));
  ASSERT_TRUE(std::equal(get<1>(z).first, get<1>(z).second, e1.begin()));
  ASSERT_TRUE(std::equal(get<2>(z).first, get<2>(z).second, e2.begin()));
  z.pop_back();
  ASSERT_TRUE(std::equal(get<0>(z).first, get<0>(z).second, e0.begin()));
  ASSERT_TRUE(std::equal(get<1>(z).first, get<1>(z).second, e1.begin()));
  ASSERT_TRUE(std::equal(get<2>(z).first, get<2>(z).second, e2.begin()));
  z.pop_back();
  ASSERT_TRUE(std::equal(get<0>(z).first, get<0>(z).second, e0.begin()));
  ASSERT_TRUE(std::equal(get<1>(z).first, get<1>(z).second, e1.begin()));
  ASSERT_TRUE(std::equal(get<2>(z).first, get<2>(z).second, e2.begin()));
  z.pop_back();
  ASSERT_TRUE(z.empty());
}

TEST(ZipListTest, TestPushPopFront) {
  zip_list<int, char, std::string> z;
  z.push_front(2, 'c', "ghi");
  z.push_front(1, 'b', "def");
  z.push_front(0, 'a', "abc");
  static constexpr auto e0 = {0, 1, 2};
  static constexpr auto e1 = {'a', 'b', 'c'};
  static constexpr auto e2 = {"abc", "def", "ghi"};
  ASSERT_TRUE(std::equal(get<0>(z).first, get<0>(z).second, e0.begin()));
  ASSERT_TRUE(std::equal(get<1>(z).first, get<1>(z).second, e1.begin()));
  ASSERT_TRUE(std::equal(get<2>(z).first, get<2>(z).second, e2.begin()));
  z.pop_front();
  ASSERT_TRUE(std::equal(get<0>(z).first, get<0>(z).second, e0.begin() + 1));
  ASSERT_TRUE(std::equal(get<1>(z).first, get<1>(z).second, e1.begin() + 1));
  ASSERT_TRUE(std::equal(get<2>(z).first, get<2>(z).second, e2.begin() + 1));
  z.pop_front();
  ASSERT_TRUE(std::equal(get<0>(z).first, get<0>(z).second, e0.begin() + 2));
  ASSERT_TRUE(std::equal(get<1>(z).first, get<1>(z).second, e1.begin() + 2));
  ASSERT_TRUE(std::equal(get<2>(z).first, get<2>(z).second, e2.begin() + 2));
}

TEST(ZipVectorTest, TestZipVector) {
  zip_vector<int,char,std::string> z;
  z.push_back(0, 'a', "abc");
  z.push_back(1, 'b', "def");
  z.push_back(2, 'c', "ghi");
  static constexpr auto e0 = {0, 1, 2};
  static constexpr auto e1 = {'a', 'b', 'c'};
  static constexpr auto e2 = {"abc", "def", "ghi"};
  ASSERT_TRUE(std::equal(get<0>(z).first, get<0>(z).second, e0.begin()));
  ASSERT_TRUE(std::equal(get<1>(z).first, get<1>(z).second, e1.begin()));
  ASSERT_TRUE(std::equal(get<2>(z).first, get<2>(z).second, e2.begin()));
}
