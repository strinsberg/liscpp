#ifndef LISCPP_VALUE_H
#define LISCPP_VALUE_H

#include "type.h"
#include <cstdint>
#include <exception>
#include <gc/gc_allocator.h>
#include <stdexcept>
#include <string>
#include <vector>

class Fn;
class Error;
class Closure;
class Stream;

class Value;
typedef std::vector<Value, gc_allocator<Value>> GcVector;
typedef std::basic_string<char, std::char_traits<char>, gc_allocator<char>>
    GcString;

class Value {
public:
  // type constructors
  Value() : m_type{ValueType::Nil}, m_val{.i = 0} {}

  // Static type constructors.
  // Trying to overload for all the types results in ambiguous overloads, so I
  // either do this, functions, or a factory class.
  static Value new_nil() { return Value(); }
  static Value new_true();
  static Value new_false();
  static Value new_int(int64_t i);
  static Value new_float(double d);
  static Value new_char(char);
  static Value new_symbol(GcString *);
  static Value new_keyword(GcString *);
  static Value new_string(GcString *);
  // static Value List(List*);
  static Value new_vector(GcVector *);
  // static Value Map(std::map<Value, Value>*); // might not work without
  // wrapper static Value Iterator(); // not sure yet
  static Value new_fn(Fn *);
  static Value new_closure(Closure *);
  static Value new_stream(Stream *);
  static Value new_error(Error *);

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
  inline bool is_iterator() const { return m_type == ValueType::Iterator; }
  inline bool is_fn() const { return m_type == ValueType::Fn; }
  inline bool is_closure() const { return m_type == ValueType::Closure; }
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
  inline double as_flt() const { return m_val.d; }
  inline const GcString &as_key() const { return *m_val.str; }
  inline const GcString &as_symbol() const { return *m_val.str; }
  inline GcString *as_str() const { return m_val.str; }
  // inline List *as_list() const { return m_val.list; }
  inline GcVector *as_vector() const { return m_val.vec; }
  // inline std::map<Value, Value> *as_map() const { return m_val.map; }
  // inline Iterator *as_iterator() const { return m_val.iter; }
  inline Fn *as_fn() const { return m_val.fn; }
  inline Closure *as_closure() const { return m_val.closure; }
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
  void to_external(std::ostream &os) const;
  void to_display(std::ostream &os) const;

private:
  ValueType m_type;
  union {
    bool b;
    char ch;
    int64_t i;
    double d;
    GcString *str;
    // List* list;
    GcVector *vec;
    // std::map<Value, Value>* map;
    // Iterator* iter;
    Fn *fn;
    Closure *closure;
    Stream *stream;
    Error *err;
  } m_val;

  // Some private constructors can make it better to initialize through the
  // static constructor functions, but in an environment that is not ambiguous.
  // But if we make them all public it can get tricky with pointers sometimes
  // being seen as int types etc. or an int literal being ambiguos with the
  // double type.
  Value(int64_t i) : m_type{ValueType::Int}, m_val{.i = i} {}
  Value(double d) : m_type{ValueType::Float}, m_val{.d = d} {}
};

std::ostream &operator<<(std::ostream &os, const Value &value);

#endif
