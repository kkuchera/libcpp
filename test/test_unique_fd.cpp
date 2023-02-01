#include "unique_fd.hpp"

#include "gtest/gtest.h"

TEST(UniqueFdTest, TestIntConversion) {
  unique_fd x{7};
  ASSERT_EQ(x.get(), 7);
}

TEST(UniqueFdTest, TestBoolConversion) {
  unique_fd x;
  ASSERT_FALSE(x);
  unique_fd y{7};
  ASSERT_TRUE(y);
}

TEST(UniqueFdTest, TestDefaultConstruction) {
  unique_fd x;
  ASSERT_EQ(x.get(), -1);
}

TEST(UniqueFdTest, TestMoveConstruction) {
  unique_fd x{9};
  unique_fd y = std::move(x);
  ASSERT_EQ(x.get(), -1);
  ASSERT_EQ(y.get(), 9);
}

TEST(UniqueFdTest, TestMoveAssignment) {
  unique_fd x{9};
  unique_fd y;
  y = std::move(x);
  ASSERT_EQ(x.get(), -1);
  ASSERT_EQ(y.get(), 9);
  y = std::move(y);
  ASSERT_EQ(y.get(), 9);
}

TEST(UniqueFdTest, TestRelease) {
  unique_fd x{9};
  ASSERT_EQ(x.release(), 9);
  ASSERT_EQ(x.get(), -1);
}

TEST(UniqueFdTest, TestReset) {
  unique_fd x{9};
  x.reset();
  ASSERT_EQ(x.get(), -1);
  x.reset(7);
  ASSERT_EQ(x.get(), 7);
}

TEST(UniqueFdTest, TestSwap) {
  unique_fd x{9};
  unique_fd y{7};
  std::swap(x, y);
  ASSERT_EQ(x.get(), 7);
  ASSERT_EQ(y.get(), 9);
}
