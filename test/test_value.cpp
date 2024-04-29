#include "type.h"
#include "value.h"
#include <gtest/gtest.h>

using namespace liscpp;

// These tests should just test the basic methods and nothing else, as much as
// is possible given the dependence Value has on all the other types.

// Nil ////////////////////////////////////////////////////////////////////////

TEST(ValueNil, accessors) {
  Value v;

  EXPECT_TRUE(v.is_nil());
  EXPECT_EQ(v.get_type(), ValueType::Nil);
  EXPECT_FALSE(v.is_truthy());
}

TEST(ValueNil, equality) {
  Value v;

  EXPECT_EQ(v, v);
  EXPECT_EQ(v, Value());
  EXPECT_NE(v, Value(int64_t(0)));
}

TEST(ValueNil, representation) {
  Value v;
  GcOsStream oss;

  v.display_rep(oss);
  EXPECT_EQ(oss.str(), "nil");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), "nil");
}

// Bool ///////////////////////////////////////////////////////////////////////

TEST(ValueBool, accessors) {
  Value t(true);
  Value f(false);

  EXPECT_TRUE(t.is_bool());
  EXPECT_TRUE(f.is_bool());

  EXPECT_EQ(t.get_type(), ValueType::Bool);
  EXPECT_EQ(f.get_type(), ValueType::Bool);

  EXPECT_TRUE(t.as_bool());
  EXPECT_FALSE(f.as_bool());

  EXPECT_TRUE(t.is_truthy());
  EXPECT_FALSE(f.is_truthy());
}

TEST(ValueBool, equality) {
  Value t(true);
  Value f(false);

  EXPECT_EQ(t, t);
  EXPECT_EQ(t, Value(true));
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Value(false));

  EXPECT_NE(t, f);
  EXPECT_NE(t, Value(false));
  EXPECT_NE(f, Value(true));
  EXPECT_NE(t, Value(int64_t(1)));
  EXPECT_NE(f, Value(int64_t(0)));
}

TEST(ValueBool, representation) {
  Value t(true);
  Value f(false);
  GcOsStream oss;

  t.display_rep(oss);
  EXPECT_EQ(oss.str(), "true");

  oss.str("");
  t.code_rep(oss);
  EXPECT_EQ(oss.str(), "true");

  oss.str("");
  f.display_rep(oss);
  EXPECT_EQ(oss.str(), "false");

  oss.str("");
  f.code_rep(oss);
  EXPECT_EQ(oss.str(), "false");
}

// Int ////////////////////////////////////////////////////////////////////////

TEST(ValueInt, accessors) {
  Value v(int64_t(42));

  EXPECT_TRUE(v.is_int());
  EXPECT_EQ(v.get_type(), ValueType::Int);
  EXPECT_EQ(v.as_int(), int64_t(42));
  EXPECT_TRUE(v.is_truthy());
}

TEST(ValueInt, equality) {
  Value v(int64_t(42));

  EXPECT_EQ(v, v);
  EXPECT_EQ(v, Value(int64_t(42)));
  EXPECT_NE(v, Value(int64_t(-42)));
  EXPECT_NE(v, Value(42.0));
}

TEST(ValueInt, representation) {
  Value v(int64_t(42));
  GcOsStream oss;

  v.display_rep(oss);
  EXPECT_EQ(oss.str(), "42");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), "42");
}

// Float //////////////////////////////////////////////////////////////////////

TEST(ValueFloat, accessors) {
  Value v(0.1234);

  EXPECT_TRUE(v.is_float());
  EXPECT_EQ(v.get_type(), ValueType::Float);
  EXPECT_FLOAT_EQ(v.as_float(), 0.1234);
  EXPECT_TRUE(v.is_truthy());
}

TEST(ValueFloat, equality) {
  Value v(0.1234);

  EXPECT_EQ(v, v);
  // NOTE float equality is not guaranteed so this EQ may not work
  EXPECT_EQ(v, Value(0.1234));
  EXPECT_NE(v, Value(10.4));
  EXPECT_NE(v, Value(int64_t(0)));
}

TEST(ValueFloat, representation) {
  Value v(0.1234);
  GcOsStream oss;

  v.display_rep(oss);
  EXPECT_EQ(oss.str(), "0.1234");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), "0.1234");
}

// Char ///////////////////////////////////////////////////////////////////////

TEST(ValueChar, accessors) {
  Value v('H');

  EXPECT_TRUE(v.is_char());
  EXPECT_EQ(v.get_type(), ValueType::Char);
  EXPECT_TRUE(v.is_truthy());
}

TEST(ValueChar, equality) {
  Value v('H');

  EXPECT_EQ(v, v);
  EXPECT_EQ(v, Value('H'));
  EXPECT_NE(v, Value('h'));
}

// TODO setup a test for these that covers all possible byte values
TEST(ValueChar, representation) {
  Value v('H');

  GcOsStream oss;
  v.display_rep(oss);
  EXPECT_EQ(oss.str(), "H");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), "\\H");
}

TEST(ValueChar, special_representation) {
  Value tab('\t');
  Value newline('\n');
  Value null('\0');
  Value space(' ');
  Value not_ascii(char(0xFF));
  Value also_not_ascii(char(0x04));

  GcOsStream oss;
  tab.display_rep(oss);
  EXPECT_EQ(oss.str(), "\t");

  oss.str("");
  newline.display_rep(oss);
  EXPECT_EQ(oss.str(), "\n");

  // For some reason comparing oss.str() and "\0" is not equal even though they
  // seem to contain the same things. I suppose it might have to do with null
  // terminated string semantics. But the below confirms that the string
  // has a character and that that character is \0.
  oss.str("");
  null.display_rep(oss);
  EXPECT_EQ(oss.str().size(), 1);
  EXPECT_EQ(oss.str().back(), '\0');

  oss.str("");
  space.display_rep(oss);
  EXPECT_EQ(oss.str(), " ");

  oss.str("");
  not_ascii.display_rep(oss);
  EXPECT_EQ(oss.str(), "\xFF");

  oss.str("");
  tab.code_rep(oss);
  EXPECT_EQ(oss.str(), "\\tab");

  oss.str("");
  newline.code_rep(oss);
  EXPECT_EQ(oss.str(), "\\newline");

  oss.str("");
  null.code_rep(oss);
  EXPECT_EQ(oss.str(), "\\null");

  oss.str("");
  space.code_rep(oss);
  EXPECT_EQ(oss.str(), "\\space");

  oss.str("");
  not_ascii.code_rep(oss);
  EXPECT_EQ(oss.str(), "\\xff");

  oss.str("");
  also_not_ascii.code_rep(oss);
  EXPECT_EQ(oss.str(), "\\x04");
}

// Keyword ////////////////////////////////////////////////////////////////////

TEST(ValueKeyword, accessors) {
  // NOTE that internal to value we do not care if a keyword starts with : or
  // not. That should be confirmed and checked elsewhere. This also concerns
  // invalid characters and spaces etc.
  // NOTE Value v(":keyword") creates a bool with a value of true. The const
  // char pointer is converted to true, according to warnings I have seen that
  // do not show up in this case but in others with passing pointers to the
  // Value constructor.
  Value v(ValueType::Keyword, new GcString(":keyword"));

  EXPECT_TRUE(v.is_keyword());
  EXPECT_EQ(v.get_type(), ValueType::Keyword);
  EXPECT_TRUE(v.is_truthy());
}

TEST(ValueKeyword, equality) {
  Value v(ValueType::Keyword, new GcString(":keyword"));

  EXPECT_EQ(v, v);
  EXPECT_EQ(v, Value(ValueType::Keyword, new GcString(":keyword")));
  EXPECT_NE(v, Value(ValueType::Keyword, new GcString(":magenta")));
  EXPECT_NE(v, Value(int64_t(0)));
}

TEST(ValueKeyword, representation) {
  Value v(ValueType::Keyword, new GcString(":keyword"));
  GcOsStream oss;

  v.display_rep(oss);
  EXPECT_EQ(oss.str(), ":keyword");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), ":keyword");
}

// Symbol /////////////////////////////////////////////////////////////////////

TEST(ValueSymbol, accessors) {
  // NOTE like keyword there is some validation that should be done on the
  // string passed to Value for symbols, but that will be done elsewhere.
  Value v(ValueType::Symbol, new GcString("hello"));

  EXPECT_TRUE(v.is_symbol());
  EXPECT_EQ(v.get_type(), ValueType::Symbol);
  EXPECT_TRUE(v.is_truthy());
}

TEST(ValueSymbol, equality) {
  Value v(ValueType::Symbol, new GcString("hello"));

  EXPECT_EQ(v, v);
  EXPECT_EQ(v, Value(ValueType::Symbol, new GcString("hello")));
  EXPECT_NE(v, Value(ValueType::Symbol, new GcString("world")));
  EXPECT_NE(v, Value(int64_t(0)));
}

TEST(ValueSymbol, representation) {
  Value v(ValueType::Symbol, new GcString("hello"));
  GcOsStream oss;

  v.display_rep(oss);
  EXPECT_EQ(oss.str(), "hello");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), "hello");
}

// Symbol /////////////////////////////////////////////////////////////////////

TEST(ValueString, accessors) {
  Value v(ValueType::String, new GcString("my string"));

  EXPECT_TRUE(v.is_string());
  EXPECT_EQ(v.get_type(), ValueType::String);
  EXPECT_TRUE(v.is_truthy());
}

TEST(ValueString, equality) {
  Value v(ValueType::String, new GcString("my string"));

  EXPECT_EQ(v, v);
  EXPECT_EQ(v, Value(ValueType::String, new GcString("my string")));
  EXPECT_NE(v, Value(ValueType::String, new GcString("your string")));
  EXPECT_NE(v, Value(int64_t(0)));
}

TEST(ValueString, representation) {
  // TODO test that the code_rep of string properly escapes all special chars
  // and other bytes. E.g. \n \t \0 \" and others as hex like \xff
  Value v(ValueType::String, new GcString("hello \"world\""));
  GcOsStream oss;

  v.display_rep(oss);
  EXPECT_EQ(oss.str(), "hello \"world\"");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), "\"hello \\\"world\\\"\"");
}

// FIXME //////////////////////////////////////////////////////////////////////

TEST(Value, accessors) {
  Value v;

  EXPECT_TRUE(v.is_nil());
  EXPECT_EQ(v.get_type(), ValueType::Nil);
  EXPECT_FALSE(v.is_truthy());
}

TEST(Value, equality) {
  Value v;

  EXPECT_EQ(v, v);
  EXPECT_EQ(v, Value());
  EXPECT_NE(v, Value(int64_t(0)));
}

TEST(Value, representation) {
  Value v;
  GcOsStream oss;

  v.display_rep(oss);
  EXPECT_EQ(oss.str(), "nil");

  oss.str("");
  v.code_rep(oss);
  EXPECT_EQ(oss.str(), "nil");
}
