#include "core.h"
#include "fn.h"
#include "value.h"
#include <gtest/gtest.h>
#include <type_traits>

// Compiler Only //////////////////////////////////////////////////////////////

TEST(CoreApplyFn, does_it_apply_a_function_properly) {
  Value args[5] = {
    Value::Int(1),
    Value::Int(2),
    Value::Int(3),
    Value::Int(4),
    Value::Int(5),
  };
  Value x = __core__::apply_fn(_plus_, args, 5);
  EXPECT_EQ(x, Value{int64_t(15)});
}


// Arithmetic /////////////////////////////////////////////////////////////////

TEST(CoreSum, does_it_sum_ints) {
  Value args[5] = {
    Value::Int(1),
    Value::Int(2),
    Value::Int(3),
    Value::Int(4),
    Value::Int(5),
  };
  Value x = __core__::sum(args, 5);
  EXPECT_EQ(x, Value{int64_t(15)});
}

TEST(CoreSum, does_it_sum_floats) {
  Value args[5] = {
    Value{1.5},
    Value{2.3},
    Value{3.4},
    Value{4.5},
    Value{5.9},
  };
  Value x = __core__::sum(args, 5);
  EXPECT_EQ(x.get_type(), ValType::Flt);
  EXPECT_DOUBLE_EQ(x.as_flt(), 17.6);
}

TEST(CoreSum, does_it_sum_mixed_ints_and_floats) {
  Value args[5] = {
    Value::Int(1),
    Value{2.3},
    Value::Int(3),
    Value{4.5},
    Value{5.9},
  };
  Value x = __core__::sum(args, 5);
  EXPECT_EQ(x.get_type(), ValType::Flt);
  EXPECT_DOUBLE_EQ(x.as_flt(), 16.7);
}

TEST(Core_plus_, does_it_point_to_core_sum) {
  ASSERT_EQ(_plus_.get_type(), ValType::Fn);
  EXPECT_EQ(*_plus_.as_fn(), Fn(__core__::sum));
}
