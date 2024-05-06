#ifndef LISCPP_VALUE_H
#define LISCPP_VALUE_H

#include "rep.h"
#include "type.h"
#include <cstdint>
#include <gc/gc_allocator.h>

namespace liscpp {

class List;
class Generator;
class Fn;
class Stream;
class Error;

class Value : Rep {
public:
  // Type constructors
  // These can be ambiguous so call them through value function constructors
  Value() : m_type{ValueType::Nil}, m_val{.i = 0} {}
  Value(bool b) : m_type{ValueType::Bool}, m_val{.b = b} {}
  Value(char ch) : m_type{ValueType::Char}, m_val{.ch = ch} {}
  Value(int64_t i) : m_type{ValueType::Int}, m_val{.i = i} {}
  Value(double d) : m_type{ValueType::Float}, m_val{.d = d} {}
  Value(ValueType t, GcString *s) : m_type{t}, m_val{.str = s} {}
  Value(List *l) : m_type{ValueType::List}, m_val{.list = l} {}
  Value(GcVector *v) : m_type{ValueType::Vector}, m_val{.vec = v} {}
  Value(GcMap *m) : m_type{ValueType::Map}, m_val{.map = m} {}
  Value(Generator *g) : m_type{ValueType::Generator}, m_val{.gen = g} {}
  Value(Fn *f) : m_type{ValueType::Fn}, m_val{.fn = f} {}
  Value(Stream *s) : m_type{ValueType::Stream}, m_val{.stream = s} {}
  Value(Error *e) : m_type{ValueType::Error}, m_val{.err = e} {}

  // predicates
  inline bool is_nil() const { return m_type == ValueType::Nil; }
  inline bool is_bool() const { return m_type == ValueType::Bool; }
  inline bool is_char() const { return m_type == ValueType::Char; }
  inline bool is_int() const { return m_type == ValueType::Int; }
  inline bool is_float() const { return m_type == ValueType::Float; }
  inline bool is_symbol() const { return m_type == ValueType::Symbol; }
  inline bool is_keyword() const { return m_type == ValueType::Keyword; }
  inline bool is_string() const { return m_type == ValueType::String; }
  inline bool is_list() const { return m_type == ValueType::List; }
  inline bool is_vector() const { return m_type == ValueType::Vector; }
  inline bool is_map() const { return m_type == ValueType::Map; }
  inline bool is_generator() const { return m_type == ValueType::Generator; }
  inline bool is_fn() const { return m_type == ValueType::Fn; }
  inline bool is_stream() const { return m_type == ValueType::Stream; }
  inline bool is_error() const { return m_type == ValueType::Error; }

  // Accessors
  // These are all unsafe, meaning that in lib and compiled code they should
  // have type checks done before calling. The reason I am not putting the
  // type checks in the accessors is that much of the time I will want to type
  // check before calling them anyway and I don't want to type check twice.
  inline bool as_bool() const { return m_val.b; }
  inline char as_char() const { return m_val.ch; }
  inline int64_t as_int() const { return m_val.i; }
  inline double as_float() const { return m_val.d; }
  inline GcString *as_keyword() const { return m_val.str; }
  inline GcString *as_symbol() const { return m_val.str; }
  inline GcString *as_string() const { return m_val.str; }
  inline List *as_list() const { return m_val.list; }
  inline GcVector *as_vector() const { return m_val.vec; }
  inline GcMap *as_map() const { return m_val.map; }
  inline Generator *as_generator() const { return m_val.gen; }
  inline Fn *as_fn() const { return m_val.fn; }
  inline Stream *as_stream() const { return m_val.stream; }
  inline Error *as_error() const { return m_val.err; }

  // util
  inline ValueType get_type() const { return m_type; }
  inline bool is_truthy() const {
    return !(is_nil() or (is_bool() and !as_bool()));
  }

  // Overloads
  bool operator==(const Value &other) const;
  bool operator!=(const Value &other) const { return !(*this == other); }

  // Representations
  void display_rep(std::ostream &os) const override;
  void code_rep(std::ostream &os) const override;

private:
  ValueType m_type;
  union {
    bool b;
    char ch;
    int64_t i;
    double d;
    GcString *str;
    List *list;
    GcVector *vec;
    GcMap *map;
    Generator *gen;
    Fn *fn;
    Stream *stream;
    Error *err;
  } m_val;
};

} // namespace liscpp

#endif
