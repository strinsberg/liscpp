#include "value.h"
#include <gtest/gtest.h>

Value __test_fn__() {
  return Value(); 
}

TEST(ValueTypes, does_it_set_its_types) {
  Value i = Value::Int(42);
  Value d = Value{0.34};
  Value k = Value::Key(":key");
  Value s = Value::Str("just a string");
  Value f = Value{__test_fn__};

  EXPECT_EQ(i.get_type(), ValType::Int);
  EXPECT_EQ(d.get_type(), ValType::Flt);
  EXPECT_EQ(k.get_type(), ValType::Key);
  EXPECT_EQ(s.get_type(), ValType::Str);
  EXPECT_EQ(f.get_type(), ValType::Fn);
}
