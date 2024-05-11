#include "value_functions.h"
#include "fn.h"
#include "generator.h"
#include "list.h"
#include "stream.h"
#include "type.h"
#include "value.h"

using namespace liscpp;

// Primitives

Value __value__::new_nil() { return Value(); }

Value __value__::new_bool(bool b) { return Value(b); }

Value __value__::new_char(char ch) { return Value(ch); }

Value __value__::new_int(int64_t i) { return Value(i); }

Value __value__::new_float(double d) { return Value(d); }

// String Types

Value __value__::new_symbol(const char *s) {
  return Value(ValueType::Symbol, new GcString(s));
}

Value __value__::new_keyword(const char *s) {
  return Value(ValueType::Keyword, new GcString(s));
}

Value __value__::new_string(const char *s) {
  return Value(ValueType::String, new GcString(s));
}

Value __value__::new_symbol(GcString *s) { return Value(ValueType::Symbol, s); }

Value __value__::new_keyword(GcString *s) {
  return Value(ValueType::Keyword, s);
}

Value __value__::new_string(GcString *s) { return Value(ValueType::String, s); }

// Collections

Value __value__::new_list(List *l) { return Value(l); }

Value __value__::new_vector(GcVector *v) { return Value(v); }

Value __value__::new_map(GcMap *m) { return Value(m); }

Value __value__::new_generator(Fn *next, Fn *is_done) {
  return Value(new Generator(next, is_done));
}

// Function
Value __value__::new_fn(Fn *f) { return Value(f); }

Value __value__::new_fn(const char *name, Value (*f)()) {
  return Value(new Fn(new GcString(name), f));
}

Value __value__::new_fn(const char *name, Value (*f)(Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value __value__::new_fn(const char *name, Value (*f)(Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value __value__::new_fn(const char *name, Value (*f)(Value, Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value __value__::new_fn(const char *name,
                        Value (*f)(Value, Value, Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value __value__::new_fn(const char *name,
                        Value (*f)(Value, Value, Value, Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value __value__::new_fn(const char *name, uint32_t arity,
                        Value (*f)(const Value args[], uint32_t n)) {
  return Value(new Fn(new GcString(name), arity, f));
}

Value __value__::new_closure(const char *name, GcVector *captures,
                             uint32_t arity,
                             Value (*fn)(GcVector *, const Value[], uint32_t)) {
  return Value(new Fn(new GcString(name), captures, arity, fn));
}

// Stream

Value __value__::new_stream(std::istream *is) { return Value(new Stream(is)); }

Value __value__::new_stream(std::ostream *os) { return Value(new Stream(os)); }

Value __value__::new_stream(std::ifstream *ifs) {
  return Value(new Stream(ifs));
}

Value __value__::new_stream(std::ofstream *ofs) {
  return Value(new Stream(ofs));
}

Value __value__::new_stream(Stream *s) { return Value(s); }

// Error

Value __value__::new_error(Error *e) { return Value(e); }

// Ostream overload

std::ostream &liscpp::operator<<(std::ostream &os, const Value &value) {
  value.display_rep(os);
  return os;
}
