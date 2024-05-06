#include "error.h"
#include "fn.h"
#include "generator.h"
#include "list.h"
#include "stream.h"
#include "type.h"
#include "value.h"
#include <cstdint>
#include <gtest/gtest.h>

using namespace liscpp;

Value __test_fn__() { return Value(); }

// GcMap and Comparator ///////////////////////////////////////////////////////

TEST(TypeGcMapComparator, test_nil_comparissons) {
  GcMapValueCompare less;
  Value nil;
  EXPECT_FALSE(less(nil, nil));

  Value b(true);
  Value ch('E');
  Value i(int64_t(42));
  Value f(double(42.234));
  EXPECT_TRUE(less(nil, b));
  EXPECT_TRUE(less(nil, ch));
  EXPECT_TRUE(less(nil, i));
  EXPECT_TRUE(less(nil, f));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_TRUE(less(nil, key));
  EXPECT_TRUE(less(nil, sym));
  EXPECT_TRUE(less(nil, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(nil, list));
  EXPECT_TRUE(less(nil, vec));
  EXPECT_TRUE(less(nil, map));
  EXPECT_TRUE(less(nil, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(nil, fn));
  EXPECT_TRUE(less(nil, stream));
  EXPECT_TRUE(less(nil, error));
}

TEST(TypeGcMapComparator, test_bool_comparissons) {
  GcMapValueCompare less;
  Value f(false);
  Value t(true);
  EXPECT_FALSE(less(t, t));
  EXPECT_FALSE(less(f, f));
  EXPECT_TRUE(less(f, t));
  EXPECT_FALSE(less(t, f));

  Value nil;
  EXPECT_FALSE(less(t, nil));
  EXPECT_FALSE(less(f, nil));

  Value ch('E');
  Value i(int64_t(1));
  Value d(double(42.234));
  EXPECT_TRUE(less(t, ch));
  EXPECT_TRUE(less(t, i));
  EXPECT_TRUE(less(t, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_TRUE(less(t, key));
  EXPECT_TRUE(less(t, sym));
  EXPECT_TRUE(less(t, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(t, list));
  EXPECT_TRUE(less(t, vec));
  EXPECT_TRUE(less(t, map));
  EXPECT_TRUE(less(t, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(t, fn));
  EXPECT_TRUE(less(t, stream));
  EXPECT_TRUE(less(t, error));
}

TEST(TypeGcMapComparator, test_char_comparissons) {
  GcMapValueCompare less;
  Value ch('A');
  Value ch2('a');
  EXPECT_FALSE(less(ch, ch));
  EXPECT_TRUE(less(ch, ch2));
  EXPECT_FALSE(less(ch2, ch));

  Value nil;
  Value b(true);
  EXPECT_FALSE(less(ch, nil));
  EXPECT_FALSE(less(ch, b));

  Value i(int64_t(65));
  Value d(double(42.234));
  EXPECT_TRUE(less(ch, i));
  EXPECT_TRUE(less(ch, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_TRUE(less(ch, key));
  EXPECT_TRUE(less(ch, sym));
  EXPECT_TRUE(less(ch, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(ch, list));
  EXPECT_TRUE(less(ch, vec));
  EXPECT_TRUE(less(ch, map));
  EXPECT_TRUE(less(ch, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(ch, fn));
  EXPECT_TRUE(less(ch, stream));
  EXPECT_TRUE(less(ch, error));
}

TEST(TypeGcMapComparator, test_int_comparissons) {
  GcMapValueCompare less;
  Value i(int64_t(42));
  Value i2(int64_t(-42));
  EXPECT_FALSE(less(i, i));
  EXPECT_FALSE(less(i, i2));
  EXPECT_TRUE(less(i2, i));

  Value nil;
  Value b(true);
  Value ch('H');
  EXPECT_FALSE(less(i, nil));
  EXPECT_FALSE(less(i, b));
  EXPECT_FALSE(less(i, ch));

  Value d(double(42.234));
  EXPECT_TRUE(less(i, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_TRUE(less(i, key));
  EXPECT_TRUE(less(i, sym));
  EXPECT_TRUE(less(i, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(i, list));
  EXPECT_TRUE(less(i, vec));
  EXPECT_TRUE(less(i, map));
  EXPECT_TRUE(less(i, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(i, fn));
  EXPECT_TRUE(less(i, stream));
  EXPECT_TRUE(less(i, error));
}

TEST(TypeGcMapComparator, test_float_comparissons) {
  GcMapValueCompare less;
  Value f(42.123);
  Value f2(42.120);
  EXPECT_FALSE(less(f, f));
  EXPECT_FALSE(less(f, f2));
  EXPECT_TRUE(less(f2, f));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  EXPECT_FALSE(less(f, nil));
  EXPECT_FALSE(less(f, b));
  EXPECT_FALSE(less(f, ch));
  EXPECT_FALSE(less(f, i));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_TRUE(less(f, key));
  EXPECT_TRUE(less(f, sym));
  EXPECT_TRUE(less(f, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(f, list));
  EXPECT_TRUE(less(f, vec));
  EXPECT_TRUE(less(f, map));
  EXPECT_TRUE(less(f, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(f, fn));
  EXPECT_TRUE(less(f, stream));
  EXPECT_TRUE(less(f, error));
}

TEST(TypeGcMapComparator, test_keyword_comparissons) {
  GcMapValueCompare less;
  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value key2(ValueType::Keyword, new GcString(":key"));
  EXPECT_FALSE(less(key, key));
  EXPECT_FALSE(less(key, key2));
  EXPECT_TRUE(less(key2, key));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(key, nil));
  EXPECT_FALSE(less(key, b));
  EXPECT_FALSE(less(key, ch));
  EXPECT_FALSE(less(key, i));
  EXPECT_FALSE(less(key, d));

  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_TRUE(less(key, sym));
  EXPECT_TRUE(less(key, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(key, list));
  EXPECT_TRUE(less(key, vec));
  EXPECT_TRUE(less(key, map));
  EXPECT_TRUE(less(key, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(key, fn));
  EXPECT_TRUE(less(key, stream));
  EXPECT_TRUE(less(key, error));
}

TEST(TypeGcMapComparator, test_symbol_comparissons) {
  GcMapValueCompare less;
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value sym2(ValueType::Symbol, new GcString("sym"));
  EXPECT_FALSE(less(sym, sym));
  EXPECT_FALSE(less(sym, sym2));
  EXPECT_TRUE(less(sym2, sym));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(sym, nil));
  EXPECT_FALSE(less(sym, b));
  EXPECT_FALSE(less(sym, ch));
  EXPECT_FALSE(less(sym, i));
  EXPECT_FALSE(less(sym, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(sym, key));
  EXPECT_TRUE(less(sym, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(sym, list));
  EXPECT_TRUE(less(sym, vec));
  EXPECT_TRUE(less(sym, map));
  EXPECT_TRUE(less(sym, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(sym, fn));
  EXPECT_TRUE(less(sym, stream));
  EXPECT_TRUE(less(sym, error));
}

TEST(TypeGcMapComparator, test_string_comparissons) {
  GcMapValueCompare less;
  Value str(ValueType::String, new GcString("string"));
  Value str2(ValueType::String, new GcString("str"));
  EXPECT_FALSE(less(str, str));
  EXPECT_FALSE(less(str, str2));
  EXPECT_TRUE(less(str2, str));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(str, nil));
  EXPECT_FALSE(less(str, b));
  EXPECT_FALSE(less(str, ch));
  EXPECT_FALSE(less(str, i));
  EXPECT_FALSE(less(str, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  EXPECT_FALSE(less(str, key));
  EXPECT_FALSE(less(str, sym));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(str, list));
  EXPECT_TRUE(less(str, vec));
  EXPECT_TRUE(less(str, map));
  EXPECT_TRUE(less(str, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(str, fn));
  EXPECT_TRUE(less(str, stream));
  EXPECT_TRUE(less(str, error));
}

TEST(TypeGcMapComparator, test_list_comparissons) {
  GcMapValueCompare less;
  // These share deep equality, but are not the same for the comparator
  // as their addresses are different (stack objects to ensure address
  // determinism)
  List l = List();
  List l2 = List();
  Value list(&l);
  Value list2(&l2);
  EXPECT_FALSE(less(list, list));
  EXPECT_FALSE(less(list2, list));
  EXPECT_TRUE(less(list, list2));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(list, nil));
  EXPECT_FALSE(less(list, b));
  EXPECT_FALSE(less(list, ch));
  EXPECT_FALSE(less(list, i));
  EXPECT_FALSE(less(list, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(list, key));
  EXPECT_FALSE(less(list, sym));
  EXPECT_FALSE(less(list, str));

  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_TRUE(less(list, vec));
  EXPECT_TRUE(less(list, map));
  EXPECT_TRUE(less(list, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(list, fn));
  EXPECT_TRUE(less(list, stream));
  EXPECT_TRUE(less(list, error));
}

TEST(TypeGcMapComparator, test_vector_comparissons) {
  GcMapValueCompare less;
  // These share deep equality, but are not the same for the comparator
  // as their addresses are different (stack objects to ensure address
  // determinism)
  GcVector v = GcVector();
  GcVector v2 = GcVector();
  Value vec(&v);
  Value vec2(&v2);
  EXPECT_FALSE(less(vec, vec));
  EXPECT_FALSE(less(vec2, vec));
  EXPECT_TRUE(less(vec, vec2));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(vec, nil));
  EXPECT_FALSE(less(vec, b));
  EXPECT_FALSE(less(vec, ch));
  EXPECT_FALSE(less(vec, i));
  EXPECT_FALSE(less(vec, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(vec, key));
  EXPECT_FALSE(less(vec, sym));
  EXPECT_FALSE(less(vec, str));

  Value list(new List());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_FALSE(less(vec, list));
  EXPECT_TRUE(less(vec, map));
  EXPECT_TRUE(less(vec, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(vec, fn));
  EXPECT_TRUE(less(vec, stream));
  EXPECT_TRUE(less(vec, error));
}

TEST(TypeGcMapComparator, test_map_comparissons) {
  GcMapValueCompare less;
  // These share deep equality, but are not the same for the comparator
  // as their addresses are different (stack objects to ensure address
  // determinism)
  GcMap m = GcMap();
  GcMap m2 = GcMap();
  Value map(&m);
  Value map2(&m2);
  EXPECT_FALSE(less(map, map));
  EXPECT_FALSE(less(map2, map));
  EXPECT_TRUE(less(map, map2));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(map, nil));
  EXPECT_FALSE(less(map, b));
  EXPECT_FALSE(less(map, ch));
  EXPECT_FALSE(less(map, i));
  EXPECT_FALSE(less(map, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(map, key));
  EXPECT_FALSE(less(map, sym));
  EXPECT_FALSE(less(map, str));

  Value list(new List());
  Value vec(new GcVector());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_FALSE(less(map, list));
  EXPECT_FALSE(less(map, vec));
  EXPECT_TRUE(less(map, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(map, fn));
  EXPECT_TRUE(less(map, stream));
  EXPECT_TRUE(less(map, error));
}

TEST(TypeGcMapComparator, test_generator_comparissons) {
  GcMapValueCompare less;
  // These share deep equality, but are not the same for the comparator
  // as their addresses are different (stack objects to ensure address
  // determinism)
  Generator g = Generator(nullptr, nullptr);
  Generator g2 = Generator(nullptr, nullptr);
  Value gen(&g);
  Value gen2(&g2);
  EXPECT_FALSE(less(gen, gen));
  EXPECT_FALSE(less(gen2, gen));
  EXPECT_TRUE(less(gen, gen2));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(gen, nil));
  EXPECT_FALSE(less(gen, b));
  EXPECT_FALSE(less(gen, ch));
  EXPECT_FALSE(less(gen, i));
  EXPECT_FALSE(less(gen, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(gen, key));
  EXPECT_FALSE(less(gen, sym));
  EXPECT_FALSE(less(gen, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  EXPECT_FALSE(less(gen, list));
  EXPECT_FALSE(less(gen, vec));
  EXPECT_FALSE(less(gen, map));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(gen, fn));
  EXPECT_TRUE(less(gen, stream));
  EXPECT_TRUE(less(gen, error));
}

TEST(TypeGcMapComparator, test_fn_comparissons) {
  GcMapValueCompare less;
  // These share deep equality, but are not the same for the comparator
  // as their addresses are different (stack objects to ensure address
  // determinism)
  Fn f = Fn(new GcString("fn"), __test_fn__);
  Fn f2 = Fn(new GcString("fn"), __test_fn__);
  Value fn(&f);
  Value fn2(&f2);
  EXPECT_FALSE(less(fn, fn));
  EXPECT_FALSE(less(fn2, fn));
  EXPECT_TRUE(less(fn, fn2));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(fn, nil));
  EXPECT_FALSE(less(fn, b));
  EXPECT_FALSE(less(fn, ch));
  EXPECT_FALSE(less(fn, i));
  EXPECT_FALSE(less(fn, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(fn, key));
  EXPECT_FALSE(less(fn, sym));
  EXPECT_FALSE(less(fn, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_FALSE(less(fn, list));
  EXPECT_FALSE(less(fn, vec));
  EXPECT_FALSE(less(fn, map));
  EXPECT_FALSE(less(fn, gen));

  Value stream(new Stream(std::cout));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_TRUE(less(fn, stream));
  EXPECT_TRUE(less(fn, error));
}

TEST(TypeGcMapComparator, test_stream_comparissons) {
  GcMapValueCompare less;
  // These share deep equality, but are not the same for the comparator
  // as their addresses are different (stack objects to ensure address
  // determinism)
  Stream s(std::cout);
  Stream s2(std::cout);
  Value stream(&s);
  Value stream2(&s2);
  EXPECT_FALSE(less(stream, stream));
  EXPECT_FALSE(less(stream2, stream));
  EXPECT_TRUE(less(stream, stream2));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(stream, nil));
  EXPECT_FALSE(less(stream, b));
  EXPECT_FALSE(less(stream, ch));
  EXPECT_FALSE(less(stream, i));
  EXPECT_FALSE(less(stream, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(stream, key));
  EXPECT_FALSE(less(stream, sym));
  EXPECT_FALSE(less(stream, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_FALSE(less(stream, list));
  EXPECT_FALSE(less(stream, vec));
  EXPECT_FALSE(less(stream, map));
  EXPECT_FALSE(less(stream, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value error(new Error(new GcString("error"), ErrorType::Error, Value()));
  EXPECT_FALSE(less(stream, fn));
  EXPECT_TRUE(less(stream, error));
}

TEST(TypeGcMapComparator, test_error_comparissons) {
  GcMapValueCompare less;
  // These share deep equality, but are not the same for the comparator
  // as their addresses are different (stack objects to ensure address
  // determinism)
  Error e(new GcString("error"), ErrorType::Error, Value());
  Error e2(new GcString("error"), ErrorType::Error, Value());
  Value error(&e);
  Value error2(&e2);
  EXPECT_FALSE(less(error, error));
  EXPECT_FALSE(less(error2, error));
  EXPECT_TRUE(less(error, error2));

  Value nil;
  Value b(true);
  Value ch('H');
  Value i(int64_t(42));
  Value d(42.123);
  EXPECT_FALSE(less(error, nil));
  EXPECT_FALSE(less(error, b));
  EXPECT_FALSE(less(error, ch));
  EXPECT_FALSE(less(error, i));
  EXPECT_FALSE(less(error, d));

  Value key(ValueType::Keyword, new GcString(":keyword"));
  Value sym(ValueType::Symbol, new GcString("symbol"));
  Value str(ValueType::String, new GcString("string"));
  EXPECT_FALSE(less(error, key));
  EXPECT_FALSE(less(error, sym));
  EXPECT_FALSE(less(error, str));

  Value list(new List());
  Value vec(new GcVector());
  Value map(new GcMap());
  Value gen(new Generator(nullptr, nullptr));
  EXPECT_FALSE(less(error, list));
  EXPECT_FALSE(less(error, vec));
  EXPECT_FALSE(less(error, map));
  EXPECT_FALSE(less(error, gen));

  Value fn(new Fn(new GcString("fn"), __test_fn__));
  Value stream(new Stream(std::cout));
  EXPECT_FALSE(less(error, fn));
  EXPECT_FALSE(less(error, stream));
}

// Type functions /////////////////////////////////////////////////////////////

// These are all representation functions so I am going to leave them untested
// for now so that I can still change them if I want. It is a lot of work to
// test these types of functions and they are the most likely to change.

// Operator<< /////////////////////////////////////////////////////////////////

TEST(OstreamOperator, gc_string_displays_like_lisp_vector) {
  GcString str("hello \"me\"");
  GcOsStream oss;
  oss << str;
  EXPECT_EQ(oss.str(), GcString("hello \"me\""));
}

TEST(OstreamOperator, gc_vector_displays_like_lisp_vector) {
  GcVector vec{Value(true), Value()};
  GcOsStream oss;
  oss << vec;
  EXPECT_EQ(oss.str(), GcString("[true nil]"));
}

TEST(OstreamOperator, gc_map_displays_like_lisp_vector) {
  GcMap map{{Value(), Value(false)}, {Value(true), Value()}};
  GcOsStream oss;
  oss << map;
  EXPECT_EQ(oss.str(), GcString("{nil false true nil}"));
}
