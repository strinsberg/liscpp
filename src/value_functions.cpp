#include "value_functions.h"
#include "fn.h"
#include "generator.h"
#include "list.h"
#include "stream.h"
#include "type.h"
#include "value.h"

using namespace liscpp;

// Primitives

Value new_nil() { return Value(); }

Value new_bool(bool b) { return Value(b); }

Value new_int(int64_t i) { return Value(i); }

Value new_float(double d) { return Value(d); }

// String Types

Value new_symbol(const char *s) {
  return Value(ValueType::Symbol, new GcString(s));
}

Value new_keyword(const char *s) {
  return Value(ValueType::Keyword, new GcString(s));
}

Value new_string(const char *s) {
  return Value(ValueType::String, new GcString(s));
}

Value new_symbol(GcString *s) { return Value(ValueType::Symbol, s); }

Value new_keyword(GcString *s) { return Value(ValueType::Keyword, s); }

Value new_string(GcString *s) { return Value(ValueType::String, s); }

// Collections

Value new_list(List *l) { return Value(l); }

Value new_vector(GcVector *v) { return Value(v); }

Value new_map(GcMap *m) { return Value(m); }

Value new_generator(Fn *next, Fn *is_done) {
  return Value(new Generator(next, is_done));
}

// Function
Value new_fn(Fn *f) { return Value(f); }

Value new_fn(const char *name, Value (*f)()) {
  return Value(new Fn(new GcString(name), f));
}

Value new_fn(const char *name, Value (*f)(Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value new_fn(const char *name, Value (*f)(Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value new_fn(const char *name, Value (*f)(Value, Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value new_fn(const char *name, Value (*f)(Value, Value, Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value new_fn(const char *name, Value (*f)(Value, Value, Value, Value, Value)) {
  return Value(new Fn(new GcString(name), f));
}

Value new_fn(const char *name, uint32_t arity,
             Value (*f)(const Value args[], uint32_t n)) {
  return Value(new Fn(new GcString(name), arity, f));
}

Value new_closure(const char *name, GcVector captures, uint32_t arity,
                  Value (*fn)(GcVector *, const Value[], uint32_t)) {
  return Value(
      new Fn(new GcString(name), new GcVector{std::move(captures)}, arity, fn));
}

// Stream

Value new_stream(std::istream *is) { return Value(new Stream(is)); }

Value new_stream(std::ostream *os) { return Value(new Stream(os)); }

Value new_stream(std::ifstream *ifs) { return Value(new Stream(ifs)); }

Value new_stream(std::ofstream *ofs) { return Value(new Stream(ofs)); }

Value new_stream(Stream *s) { return Value(s); }

// Error

Value new_error(Error *e) { return Value(e); }

// Ostream overload

std::ostream &operator<<(std::ostream &os, const Value &value) {
  value.display_rep(os);
  return os;
}
