#include "value.h"
#include <gtest/gtest.h>

TEST(ValueTemp, does_it_add) {
  Value v;
  EXPECT_EQ(v.add(10, 33), 43);
}
