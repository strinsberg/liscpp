#ifndef LISCPP_FN_H
#define LISCPP_FN_H

#include "rep.h"
#include "type.h"
#include <cstdint>

namespace liscpp {

class Fn : public Rep {
public:
  // Constructors overloaded for function arity
  Fn(GcString *name, Value (*f)());
  Fn(GcString *name, Value (*f)(Value));
  Fn(GcString *name, Value (*f)(Value, Value));
  Fn(GcString *name, Value (*f)(Value, Value, Value));
  Fn(GcString *name, Value (*f)(Value, Value, Value, Value));
  Fn(GcString *name, Value (*f)(Value, Value, Value, Value, Value));
  Fn(GcString *name, uint32_t arity, Value (*f)(const Value[], uint32_t));
  Fn(GcString *name, GcVector *captures, uint32_t arity,
     Value (*f)(GcVector *, const Value[], uint32_t));

  // Other constructors
  Fn(const Fn &f)
      : m_name{f.m_name}, m_arity{f.m_arity}, m_type{f.m_type},
        m_captures{f.m_captures} {}

  // Accessors
  inline const GcString &get_name() const { return *m_name; }
  inline uint32_t get_arity() const { return m_arity; }
  inline FnType get_type() const { return m_type; }
  inline GcVector *get_captures() const { return m_captures; }

  // Overloads
  Value operator()(const Value[], uint32_t) const;

  // Representation
  void code_rep(std::ostream &) const override;
  void display_rep(std::ostream &) const override;

private:
  GcString *m_name;
  uint32_t m_arity;
  FnType m_type;
  GcVector *m_captures;

  union {
    Value (*fn0)();
    Value (*fn1)(Value);
    Value (*fn2)(Value, Value);
    Value (*fn3)(Value, Value, Value);
    Value (*fn4)(Value, Value, Value, Value);
    Value (*fn5)(Value, Value, Value, Value, Value);
    Value (*fn_any)(const Value[], uint32_t);
    Value (*fn_closure)(GcVector *, const Value[], uint32_t);
  } m_fn;
};

} // namespace liscpp

#endif
