#include "error.h"
#include "fn.h"
#include "stream.h"
#include "value.h"
#include <gtest/gtest.h>

// Test function(s) to pass to Values where needed
namespace liscpp_value_tests {
Value test_fn() { return Value(); }
} // namespace liscpp_value_tests

// Bool Tests /////////////////////////////////////////////////////////////////

TEST(ValueBool, does_it_work_as_true) {
  Value t = Value::new_true();
  ASSERT_TRUE(t.is_bool());
  EXPECT_TRUE(t.as_bool());

  std::stringstream ss("");
  t.to_external(ss);
  EXPECT_EQ(ss.str(), "true");

  ss.str("");
  t.to_display(ss);
  EXPECT_EQ(ss.str(), "true");
}

TEST(ValueBool, does_it_work_as_false) {
  Value f = Value::new_false();
  EXPECT_TRUE(f.is_bool());
  EXPECT_FALSE(f.as_bool());

  std::stringstream ss("");
  f.to_external(ss);
  EXPECT_EQ(ss.str(), "false");

  ss.str("");
  f.to_display(ss);
  EXPECT_EQ(ss.str(), "false");
}

// Vector Tests ///////////////////////////////////////////////////////////////

TEST(ValueVector, is_it_properly_created_and_displayed) {
  Value v = Value::new_vector(new GcVector());
  ASSERT_TRUE(v.is_vector());

  std::stringstream ss("");
  v.to_external(ss);
  EXPECT_EQ(ss.str(), "[]");

  GcVector *vec = v.as_vector();
  vec->push_back(Value::new_true());
  vec->push_back(Value::new_int(10));
  vec->push_back(Value::new_string(new GcString("hello")));
  vec->push_back(Value());

  ss.str("");
  v.to_external(ss);
  EXPECT_EQ(ss.str(), "[true, 10, \"hello\", nil]");
}

TEST(ValueVector, does_it_have_deep_equality) {
  Value v = Value::new_vector(
      new GcVector{Value::new_true(), Value::new_int(10),
                   Value::new_string(new GcString("hello")), Value()});
  Value v2 = Value::new_vector(
      new GcVector{Value::new_true(), Value::new_int(10),
                   Value::new_string(new GcString("hello")), Value()});
  EXPECT_EQ(v, v2);

  (*v2.as_vector())[0] = Value::new_false();
  EXPECT_NE(v, v2);
}

// Test Value Truthyness //////////////////////////////////////////////////////

TEST(ValueIsTruthy, do_all_values_match_expected_truth) {
  EXPECT_FALSE(Value().is_truthy());
  EXPECT_FALSE(Value::new_false().is_truthy());

  EXPECT_TRUE(Value::new_true().is_truthy());
  EXPECT_TRUE(Value::new_char('\0').is_truthy());
  EXPECT_TRUE(Value::new_char('&').is_truthy());
  EXPECT_TRUE(Value::new_int(0).is_truthy());
  EXPECT_TRUE(Value::new_int(29).is_truthy());
  EXPECT_TRUE(Value::new_float(0.0).is_truthy());
  EXPECT_TRUE(Value::new_float(123.456).is_truthy());
  EXPECT_TRUE(Value::new_symbol(new GcString("cons")).is_truthy());
  EXPECT_TRUE(Value::new_keyword(new GcString(":arg")).is_truthy());
  EXPECT_TRUE(Value::new_string(new GcString("")).is_truthy());
  EXPECT_TRUE(Value::new_string(new GcString("hello")).is_truthy());
  EXPECT_TRUE(Value::new_vector(new GcVector()).is_truthy());
  EXPECT_TRUE(
      Value::new_vector(new GcVector{Value(), Value::new_false()}).is_truthy());
  EXPECT_TRUE(Value::new_fn(new Fn(liscpp_value_tests::test_fn)).is_truthy());
  EXPECT_TRUE(Value::new_stream(new Stream(&std::cout)).is_truthy());
  EXPECT_TRUE(Value::new_error(new Error("none", Value())).is_truthy());
}
