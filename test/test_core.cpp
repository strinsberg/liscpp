#include "core.h"
#include "value.h"
#include "value_functions.h"
#include <gtest/gtest.h>

using namespace liscpp;
using liscpp::__core__::call;

TEST(CoreLibArithmetic, sum_with_no_args) {
  std::cout << Value(int64_t(5)) << std::endl;
  const Value args[] = {};
  Value result = call(core::_plus_.as_fn(), args, 0);
  EXPECT_EQ(result, Value(int64_t(0)));
}

TEST(CoreLibArithmetic, sum_with_one_arg) {
  const Value args[] = {Value(int64_t(42))};
  Value result = call(core::_plus_.as_fn(), args , 1);
  EXPECT_EQ(result, Value(int64_t(42)));
}

TEST(CoreLibArithmetic, sum_with_many_args) {
  const Value args[] = {Value(int64_t(1)), Value(int64_t(2)), Value(int64_t(3)),
                        Value(int64_t(4)), Value(int64_t(5))};
  Value result = call(core::_plus_.as_fn(), args, 5);
  EXPECT_EQ(result, Value(int64_t(15)));
}
