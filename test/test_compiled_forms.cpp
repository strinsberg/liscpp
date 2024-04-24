#include "core.h"
#include "value.h"
#include <gtest/gtest.h>

/* These tests are a place to experiment with different possibilities of
 * generated code for forms that are essentially compiler macros. Things will
 * change and this may eventually just be removed.
 *
 * The format will be a block of code that is an expression and then a single
 * expectation on the value of the return of that expression. Kind of like if
 * we had a test where we evaluated an expression and checked that it had
 * the right result.
 *
 * NOTE in compiled code unless specifically called for all calls to core
 * functions will not use the namespace. We will include a using namespace core
 * in compiled code so that users do not need to use core on everthing and so
 * that if a user shadows something it will work without needing to shadow using
 * the namespace for core.
 */

TEST(CompiledCode, let) {
  // (let [a 10 b 3] (+ a 6) (+ a b))

  Value result;
  {
    Value a = Value::new_int(10);
    Value b = Value::new_int(3);

    Value c = Value::new_int(6);
    Value args1[] = {a, c};
    __core__::apply_fn(core::_plus_, args1, 2);

    Value args2[] = {a, b};
    result = __core__::apply_fn(core::_plus_, args2, 2);
  }

  EXPECT_EQ(result, Value::new_int(13));
}

TEST(CompiledCode, if) {
  // internally this will probably transform to cond first
  // (if (= 10 5) 1 0)

  Value result;
  {
    Value a = Value::new_int(10);
    Value b = Value::new_int(5);
    Value args[] = {a, b};
    Value cond = __core__::apply_fn(core::_equal_, args, 2);
    if (cond.is_truthy()) {
      result = Value::new_int(1);
    } else {
      result = Value::new_int(0);
    }
  }

  EXPECT_EQ(result, Value::new_int(0));
}

TEST(CompiledCode, cond) {
  // can end with :else or implicitly add :else nil
  // (cond (= 10 5) 1 (= 3 3) 20)

  Value result;
  {
    Value a = Value::new_int(10);
    Value b = Value::new_int(5);
    Value args1[] = {a, b};
    Value cond1 = __core__::apply_fn(core::_equal_, args1, 2);

    Value x = Value::new_int(3);
    Value y = Value::new_int(3);
    Value args2[] = {x, y};
    Value cond2 = __core__::apply_fn(core::_equal_, args2, 2);

    if (cond1.is_truthy()) {
      result = Value::new_int(1);
    } else if (cond2.is_truthy()) {
      result = Value::new_int(20);
    } else {
      result = Value();
    }
  }

  EXPECT_EQ(result, Value::new_int(20));
}
