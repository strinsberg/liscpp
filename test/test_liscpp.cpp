#include "gc/gc.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  // Start the gc platform, not sure how this works with gtest
  GC_INIT();

  // Setup and run all gtest tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
