#include "fn.h"
#include "generator.h"
#include "list.h"
#include "stream.h"
#include "value_functions.h"
#include "error.h"
#include <fstream>
#include <gtest/gtest.h>

using namespace liscpp;

// Helpers ////////////////////////////////////////////////////////////////////

Value __test_fn0__() { return Value(); }
Value __test_fn1__(Value) { return Value(); }
Value __test_fn2__(Value, Value) { return Value(); }
Value __test_fn3__(Value, Value, Value) { return Value(); }
Value __test_fn4__(Value, Value, Value, Value) { return Value(); }
Value __test_fn5__(Value, Value, Value, Value, Value) { return Value(); }
Value __test_fn_any__(const Value[], uint32_t) { return Value(); }
Value __test_closure__(GcVector *, const Value[], uint32_t) { return Value(); }

// Tests //////////////////////////////////////////////////////////////////////

TEST(ValueFunctionsNewPrimitives, constructor_functions) {
  ASSERT_TRUE(__value__::new_nil().is_nil());

  Value t = __value__::new_bool(true);
  Value f = __value__::new_bool(false);
  ASSERT_TRUE(t.is_bool());
  EXPECT_TRUE(t.is_truthy());
  ASSERT_TRUE(f.is_bool());
  EXPECT_FALSE(f.is_truthy());

  Value ch = __value__::new_char('s');
  ASSERT_TRUE(ch.is_char());
  EXPECT_EQ(ch.as_char(), 's');

  Value i = __value__::new_int(42);
  ASSERT_TRUE(i.is_int());
  EXPECT_EQ(i.as_int(), 42);

  Value flt = __value__::new_float(42.123);
  ASSERT_TRUE(flt.is_float());
  EXPECT_FLOAT_EQ(flt.as_float(), 42.123);
}

TEST(ValueFunctionsStringBasedValues, const_char_constructor_functions) {
  Value key = __value__::new_keyword(":keyword");
  ASSERT_TRUE(key.is_keyword());
  EXPECT_EQ(*key.as_keyword(), GcString(":keyword"));

  Value sym = __value__::new_symbol("symbol");
  ASSERT_TRUE(sym.is_symbol());
  EXPECT_EQ(*sym.as_symbol(), GcString("symbol"));

  Value str = __value__::new_string("hello, world");
  ASSERT_TRUE(str.is_string());
  EXPECT_EQ(*str.as_string(), GcString("hello, world"));
}

// The method of passing pointers around in following tests is only useful
// because we do not ever free pointers since the underlying logic expects
// garbage collection. What this does is keep allocation to a minimum during
// the tests and should make it easier to track down memory issues if I am not
// using the garbage collection right. However, I am not sure I should do it
// this way and might just change it back to use new and rely on the garbage
// collector in the tests as in a compiled program.

TEST(ValueFunctionsStringBasedValues, gc_string_constructor_functions) {
  GcString k(":keyword");
  Value key = __value__::new_keyword(&k);
  ASSERT_TRUE(key.is_keyword());
  EXPECT_EQ(*key.as_keyword(), GcString(":keyword"));

  GcString s("symbol");
  Value sym = __value__::new_symbol(&s);
  ASSERT_TRUE(sym.is_symbol());
  EXPECT_EQ(*sym.as_symbol(), GcString("symbol"));

  GcString st("hello, world");
  Value str = __value__::new_string(&st);
  ASSERT_TRUE(str.is_string());
  EXPECT_EQ(*str.as_string(), GcString("hello, world"));
}

TEST(ValueFunctionsCollections, constructor_functions) {
  List l;
  Value list = __value__::new_list(&l);
  ASSERT_TRUE(list.is_list());
  EXPECT_EQ(list.as_list(), &l);

  GcVector v;
  Value vec = __value__::new_vector(&v);
  ASSERT_TRUE(vec.is_vector());
  EXPECT_EQ(vec.as_vector(), &v);

  GcMap m;
  Value map = __value__::new_map(&m);
  ASSERT_TRUE(map.is_map());
  EXPECT_EQ(map.as_map(), &m);

  Value gen = __value__::new_generator(nullptr, nullptr);
  ASSERT_TRUE(gen.is_generator());
}

TEST(ValueFunctionsFn, constructor_functions) {
  GcString name("fn");
  Fn f0(&name, __test_fn0__);
  Value fn = __value__::new_fn(&f0);
  ASSERT_TRUE(fn.is_fn());
  EXPECT_EQ(fn.as_fn(), &f0);

  Value fn0 = __value__::new_fn("fn0", __test_fn0__);
  ASSERT_TRUE(fn0.is_fn());
  EXPECT_EQ(fn0.as_fn()->get_name(), GcString("fn0"));
  EXPECT_EQ(fn0.as_fn()->get_arity(), 0);

  Value fn1 = __value__::new_fn("fn1", __test_fn1__);
  ASSERT_TRUE(fn1.is_fn());
  EXPECT_EQ(fn1.as_fn()->get_name(), GcString("fn1"));
  EXPECT_EQ(fn1.as_fn()->get_arity(), 1);

  Value fn2 = __value__::new_fn("fn2", __test_fn2__);
  ASSERT_TRUE(fn2.is_fn());
  EXPECT_EQ(fn2.as_fn()->get_name(), GcString("fn2"));
  EXPECT_EQ(fn2.as_fn()->get_arity(), 2);

  Value fn3 = __value__::new_fn("fn3", __test_fn3__);
  ASSERT_TRUE(fn3.is_fn());
  EXPECT_EQ(fn3.as_fn()->get_name(), GcString("fn3"));
  EXPECT_EQ(fn3.as_fn()->get_arity(), 3);

  Value fn4 = __value__::new_fn("fn4", __test_fn4__);
  ASSERT_TRUE(fn4.is_fn());
  EXPECT_EQ(fn4.as_fn()->get_name(), GcString("fn4"));
  EXPECT_EQ(fn4.as_fn()->get_arity(), 4);

  Value fn5 = __value__::new_fn("fn5", __test_fn5__);
  ASSERT_TRUE(fn5.is_fn());
  EXPECT_EQ(fn5.as_fn()->get_name(), GcString("fn5"));
  EXPECT_EQ(fn5.as_fn()->get_arity(), 5);

  // remember arity for Fn is the min number of args needed
  Value fn_any = __value__::new_fn("fn-any", 9, __test_fn_any__);
  ASSERT_TRUE(fn_any.is_fn());
  EXPECT_EQ(fn_any.as_fn()->get_name(), GcString("fn-any"));
  EXPECT_EQ(fn_any.as_fn()->get_arity(), 9);

  // remember the capture vector is moved into the internal
  GcVector cap{Value()};
  Value fn_closure =
      __value__::new_closure("closure", &cap, 0, __test_closure__);
  ASSERT_TRUE(fn_closure.is_fn());
  EXPECT_EQ(fn_closure.as_fn()->get_name(), GcString("closure"));
  EXPECT_EQ(fn_closure.as_fn()->get_arity(), 0);
  EXPECT_EQ(fn_closure.as_fn()->get_captures(), &cap);
}

TEST(ValueFunctionsStream, constructor_functions) {
  Value os = __value__::new_stream(&std::cout);
  ASSERT_TRUE(os.is_stream());

  Value is = __value__::new_stream(&std::cin);
  ASSERT_TRUE(is.is_stream());

  std::ifstream ifs;
  Value ifstream = __value__::new_stream(&ifs);
  ASSERT_TRUE(ifstream.is_stream());

  std::ofstream ofs;
  Value ofstream = __value__::new_stream(&ofs);
  ASSERT_TRUE(ofstream.is_stream());

  Stream s(&std::cout);
  Value stream = __value__::new_stream(&s);
  ASSERT_TRUE(stream.is_stream());
  EXPECT_EQ(stream.as_stream(), &s);
}

TEST(ValueFunctionsError, constructor_functions) {
  GcString what("error message");
  Error err(&what, ErrorType::Error, Value());
  Value error = __value__::new_error(&err);
  ASSERT_TRUE(error.is_error());
  EXPECT_EQ(error.as_error(), &err);
  EXPECT_STREQ(error.as_error()->what(), "error message");
  EXPECT_EQ(error.as_error()->get_data(), Value());
}
