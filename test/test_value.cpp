#include "fn.h"
#include "value.h"
#include <gtest/gtest.h>

// Test function(s) to pass to Values where needed
Value __test_fn__() { return Value(); }

// Value Tests ////////////////////////////////////////////////////////////////

TEST(ValueTypes, does_it_set_its_types) {
  Value i = Value::new_int(42);
  Value d = Value::new_float(0.34);
  Value k = Value::new_keyword(":key");
  Value s = Value::new_string(new std::string("just a string"));
  Value f = Value::new_fn(new Fn(__test_fn__));

  EXPECT_TRUE(i.is_int());
  EXPECT_TRUE(d.is_float());
  EXPECT_TRUE(k.is_keyword());
  EXPECT_TRUE(s.is_string());
  EXPECT_TRUE(f.is_fn());
}
