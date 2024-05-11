#include "core.h"
#include "error.h"
#include "value.h"
#include "value_functions.h"
#include <gtest/gtest.h>

using namespace liscpp;
using liscpp::__core__::call;

TEST(CoreLibArithmetic, sum_with_no_args) {
  const Value args[] = {};
  Value result = call(core::_plus_.as_fn(), args, 0);
  EXPECT_EQ(result, Value(int64_t(0)));
}

TEST(CoreLibArithmetic, sum_with_one_arg) {
  const Value int_args[] = {Value(int64_t(42))};
  Value int_result = call(core::_plus_.as_fn(), int_args, 1);
  EXPECT_EQ(int_result, Value(int64_t(42)));

  const Value float_args[] = {Value(0.1234)};
  Value float_result = call(core::_plus_.as_fn(), float_args, 1);
  ASSERT_TRUE(float_result.is_float());
  EXPECT_FLOAT_EQ(float_result.as_float(), 0.1234);
}

TEST(CoreLibArithmetic, sum_with_many_args) {
  const Value int_args[] = {Value(int64_t(1)), Value(int64_t(2)),
                            Value(int64_t(3)), Value(int64_t(4)),
                            Value(int64_t(5))};
  Value int_result = call(core::_plus_.as_fn(), int_args, 5);
  EXPECT_EQ(int_result, Value(int64_t(15)));

  const Value float_args[] = {Value(0.1), Value(0.2), Value(0.3), Value(0.4),
                              Value(0.5)};
  Value float_result = call(core::_plus_.as_fn(), float_args, 5);
  ASSERT_TRUE(float_result.is_float());
  EXPECT_FLOAT_EQ(float_result.as_float(), 1.5);

  const Value mixed_args[] = {Value(int64_t(1)), Value(0.2), Value(int64_t(3)),
                              Value(int64_t(4)), Value(0.5)};
  Value mixed_result = call(core::_plus_.as_fn(), mixed_args, 5);
  ASSERT_TRUE(mixed_result.is_float());
  EXPECT_EQ(mixed_result.as_float(), 8.7);
}

TEST(CoreLibArithmetic, sum_with_invalid_arg_type) {
  const Value args[] = {Value(int64_t(1)), Value()};

  EXPECT_THROW(call(core::_plus_.as_fn(), args, 2), Error *);
}
