#include "core.h"
#include "fn.h"
#include "value.h"
#include <gtest/gtest.h>
#include <type_traits>

// Compiler Only //////////////////////////////////////////////////////////////

TEST(CoreApplyFn, does_it_apply_a_function_properly) {
  Value args[5] = {
      Value::new_int(1), Value::new_int(2), Value::new_int(3),
      Value::new_int(4), Value::new_int(5),
  };
  Value x = __core__::apply_fn(core::_plus_, args, 5);
  EXPECT_EQ(x, Value::new_int(15));
}

// Arithmetic /////////////////////////////////////////////////////////////////

TEST(CoreSum, does_it_sum_ints) {
  Value args[5] = {
      Value::new_int(1), Value::new_int(2), Value::new_int(3),
      Value::new_int(4), Value::new_int(5),
  };
  Value x = __core__::sum(args, 5);
  EXPECT_EQ(x, Value::new_int(15));
}

TEST(CoreSum, does_it_sum_floats) {
  Value args[5] = {
      Value::new_float(1.5), Value::new_float(2.3), Value::new_float(3.4),
      Value::new_float(4.5), Value::new_float(5.9),
  };
  Value x = __core__::sum(args, 5);
  EXPECT_TRUE(x.is_float());
  EXPECT_DOUBLE_EQ(x.as_flt(), 17.6);
}

TEST(CoreSum, does_it_sum_mixed_ints_and_floats) {
  Value args[5] = {
      Value::new_int(1),     Value::new_float(2.3), Value::new_int(3),
      Value::new_float(4.5), Value::new_float(5.9),
  };
  Value x = __core__::sum(args, 5);
  EXPECT_TRUE(x.is_float());
  EXPECT_DOUBLE_EQ(x.as_flt(), 16.7);
}

TEST(Core_plus_, does_it_point_to_core_sum) {
  ASSERT_TRUE(core::_plus_.is_fn());
  EXPECT_EQ(*core::_plus_.as_fn(), Fn(new GcString("core/+"), 0, __core__::sum));
}
