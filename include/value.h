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

class Fn;
class Error;
class Closure;
class Stream;

enum class ValType {
  Nil,
  Bool,
  Char,
  Int,
  Flt,
  Key,
  Str,
  Fn,
  Clos,
  Strm,
  Err,
};

union ValUnion {
  ValUnion() : i{0} {}
  ValUnion(bool b) : b{b} {}
  ValUnion(uint32_t u) : u{u} {}
  ValUnion(int64_t i) : i{i} {}
  ValUnion(double d) : d{d} {}
  ValUnion(std::string *s) : s{s} {}
  ValUnion(Fn *f) : f{f} {}
  ValUnion(Error *e) : e{e} {}
  ValUnion(Stream *s) : st{s} {}

  bool b;
  uint32_t u;
  int64_t i;
  double d;
  std::string *s;
  Fn *f;
  Closure *c;
  Stream *st;
  Error *e;
};

class Value {
public:
  // type constructors
  Value() : m_type{ValType::Nil}, m_val{} {}
  Value(bool b) : m_type{ValType::Bool}, m_val{b} {}
  Value(uint32_t u, ValType type) : m_type{type}, m_val{u} {}
  Value(int64_t i) : m_type{ValType::Int}, m_val{i} {}
  Value(double d) : m_type{ValType::Flt}, m_val{d} {}
  Value(std::string *s) : m_type{ValType::Str}, m_val{s} {}
  Value(Fn *f) : m_type{ValType::Fn}, m_val{f} {}
  Value(Error *e) : m_type{ValType::Err}, m_val{e} {}
  Value(Stream *s) : m_type{ValType::Strm}, m_val{s} {}

  // raw fn pointer constructors
  Value(Value (*f)());
  Value(Value (*f)(Value));
  Value(Value (*f)(Value, Value));
  Value(Value (*f)(Value, Value, Value));
  Value(Value (*f)(Value, Value, Value, Value));
  Value(Value (*f)(Value, Value, Value, Value, Value));
  Value(Value (*f)(const Value[], uint32_t));

  // Static type constructor methods
  static Value True();
  static Value False();
  static Value Int(int64_t);
  static Value Char(uint32_t);
  static Value Key(const std::string&);
  static Value Str(const std::string&);

  // predicates
  inline bool is_nil() const { return m_type == ValType::Nil; }
  inline bool is_bool() const { return m_type == ValType::Bool; }
  inline bool is_char() const { return m_type == ValType::Char; }
  inline bool is_int() const { return m_type == ValType::Int; }
  inline bool is_flt() const { return m_type == ValType::Flt; }
  inline bool is_key() const { return m_type == ValType::Key; }
  inline bool is_str() const { return m_type == ValType::Str; }
  inline bool is_fn() const { return m_type == ValType::Fn; }
  inline bool is_strm() const { return m_type == ValType::Strm; }
  inline bool is_err() const { return m_type == ValType::Err; }

  // unsafe accessors
  inline bool as_bool() const { return m_val.b; }
  inline uint32_t as_char() const { return m_val.u; }
  inline int64_t as_int() const { return m_val.i; }
  inline double as_flt() const { return m_val.d; }
  inline const std::string& as_key() const { return *m_val.s; }
  // TODO if a value is immutable these should return const&
  inline std::string *as_str() const { return m_val.s; }
  inline Fn *as_fn() const { return m_val.f; }
  inline Error *as_error() const { return m_val.e; }
  inline Stream *as_strm() const { return m_val.st; }

  // safe accessors
  ValType get_type() const { return m_type; }
  bool get_bool() const;
  int64_t get_int() const;
  double get_flt() const;
  const std::string& get_key() const;
  std::string *get_str() const;
  Fn *get_fn() const;
  Error *get_error() const;

  // util
  bool is_truthy() const;
  const std::string type_string() const;

  // Overloads
  bool operator==(const Value &other) const;
  bool operator!=(const Value &other) const { return !(*this == other); }

  // Representations
  void to_external(std::ostream& os) const;
  void to_display(std::ostream& os) const;

private:
  ValType m_type;
  ValUnion m_val;
};

std::ostream& operator<<(std::ostream& os, const Value& value);

#endif
