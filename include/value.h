#ifndef LISCPP_VALUE_H
#define LISCPP_VALUE_H

#include <cstdint>
#include <exception>
#include <stdexcept>
#include <string>

/* Value types for the dynamic lisp types.
 *
 * Several different types and their enums/unions are all declared in this
 * header because they are circular dependencies and it is easier to keep them
 * all in the same place.
 */

class Value;
class Error;

// Function Types /////////////////////////////////////////////////////////////

enum class FnType {
  Fn0,
  Fn1,
  Fn2,
  Fn3,
  Fn4,
  Fn5,
  FnAny,
};

union FnUnion {
  FnUnion(Value (*f)()) : fn0{f} {}
  FnUnion(Value (*f)(Value)) : fn1{f} {}
  FnUnion(Value (*f)(Value, Value)) : fn2{f} {}
  FnUnion(Value (*f)(Value, Value, Value)) : fn3{f} {}
  FnUnion(Value (*f)(Value, Value, Value, Value)) : fn4{f} {}
  FnUnion(Value (*f)(Value, Value, Value, Value, Value)) : fn5{f} {}
  FnUnion(Value (*f)(const Value[], uint32_t)) : fn_any{f} {}

  Value (*fn0)();
  Value (*fn1)(Value);
  Value (*fn2)(Value, Value);
  Value (*fn3)(Value, Value, Value);
  Value (*fn4)(Value, Value, Value, Value);
  Value (*fn5)(Value, Value, Value, Value, Value);
  Value (*fn_any)(const Value[], uint32_t);
};

class Fn {
public:
  Fn(Value (*f)()) : m_type{FnType::Fn0}, m_fn{f} {}
  Fn(Value (*f)(Value)) : m_type{FnType::Fn1}, m_fn{f} {}
  Fn(Value (*f)(Value, Value)) : m_type{FnType::Fn2}, m_fn{f} {}
  Fn(Value (*f)(Value, Value, Value)) : m_type{FnType::Fn3}, m_fn{f} {}
  Fn(Value (*f)(Value, Value, Value, Value)) : m_type{FnType::Fn4}, m_fn{f} {}
  Fn(Value (*f)(Value, Value, Value, Value, Value))
      : m_type{FnType::Fn5}, m_fn{f} {}
  Fn(Value (*f)(const Value[], uint32_t)) : m_type{FnType::FnAny}, m_fn{f} {}

  Value operator()(const Value[], uint32_t n);
  bool operator==(const Fn &other) const;

private:
  FnType m_type;
  FnUnion m_fn;
};

// Value //////////////////////////////////////////////////////////////////////

enum class ValType {
  Nil,
  Int,
  Flt,
  Key,
  Str,
  Fn,
  Err,
};

union ValUnion {
  ValUnion() : i{0} {}
  ValUnion(int64_t i) : i{i} {}
  ValUnion(double d) : d{d} {}
  ValUnion(std::string *s) : s{s} {}
  ValUnion(Fn *f) : f{f} {}
  ValUnion(Error *e) : e{e} {}

  int64_t i;
  double d;
  std::string *s;
  Fn *f;
  Error *e;
};

class Value {
public:
  // type constructors
  Value() : m_type{ValType::Nil}, m_val{} {}
  Value(int64_t i) : m_type{ValType::Int}, m_val{i} {}
  Value(double d) : m_type{ValType::Flt}, m_val{d} {}
  Value(std::string *s) : m_type{ValType::Str}, m_val{s} {}
  Value(Fn *f) : m_type{ValType::Fn}, m_val{f} {}
  Value(Error *e) : m_type{ValType::Err}, m_val{e} {}

  // raw fn pointer constructors
  Value(Value (*f)()) : m_type{ValType::Fn}, m_val{new Fn(f)} {}
  Value(Value (*f)(Value)) : m_type{ValType::Fn}, m_val{new Fn(f)} {}
  Value(Value (*f)(Value, Value)) : m_type{ValType::Fn}, m_val{new Fn(f)} {}
  Value(Value (*f)(Value, Value, Value))
      : m_type{ValType::Fn}, m_val{new Fn(f)} {}
  Value(Value (*f)(Value, Value, Value, Value))
      : m_type{ValType::Fn}, m_val{new Fn(f)} {}
  Value(Value (*f)(Value, Value, Value, Value, Value))
      : m_type{ValType::Fn}, m_val{new Fn(f)} {}
  Value(Value (*f)(const Value[], uint32_t))
      : m_type{ValType::Fn}, m_val{new Fn(f)} {}

  // Static type constructor methods
  static Value Int(int64_t);
  static Value Key(const std::string&);
  static Value Str(const std::string&);

  // predicates
  inline bool is_nil() const { return m_type == ValType::Nil; }
  inline bool is_int() const { return m_type == ValType::Int; }
  inline bool is_flt() const { return m_type == ValType::Flt; }
  inline bool is_str() const { return m_type == ValType::Str; }
  inline bool is_fn() const { return m_type == ValType::Fn; }
  inline bool is_err() const { return m_type == ValType::Err; }

  // accessors
  // unsafe
  inline int64_t as_int() const { return m_val.i; }
  inline double as_flt() const { return m_val.d; }
  inline std::string *as_str() const { return m_val.s; }
  inline Fn *as_fn() const { return m_val.f; }
  inline Error *as_error() const { return m_val.e; }
  // safe
  ValType get_type() const { return m_type; }
  int64_t get_int() const;
  int64_t get_flt() const;
  std::string *get_str() const;
  Fn *get_fn() const;
  Error *get_error() const;

  // Overloads
  bool operator==(const Value &other) const;

private:
  ValType m_type;
  ValUnion m_val;
};

// Error Type /////////////////////////////////////////////////////////////////

// TODO we might need some error types? or the error needs to hold a keyword
// or something to identify the type for the user.
class Error : public std::exception {
public:
  Error(const std::string &message, Value data)
      : m_message{message}, m_data{data} {}

  const char *what() const throw();

private:
  std::string m_message;
  Value m_data;
};

#endif
