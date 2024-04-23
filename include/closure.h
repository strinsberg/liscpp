#ifndef LISCPP_CLOSURE_H
#define LISCPP_CLOSURE_H

#include "value.h"
#include <cstdint>
#include <vector>

class Closure {
public:
  Closure(std::vector<Value> *captured,
          Value (*fn)(std::vector<Value> *, Value[], uint32_t))
      : m_captured{captured}, m_fn{fn} {}

  inline Value apply(Value args[], uint32_t n) {
    return m_fn(m_captured, args, n);
  }

private:
  std::vector<Value> *m_captured;
  Value (*m_fn)(std::vector<Value> *, Value[], uint32_t);
};

#endif
