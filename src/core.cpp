#include "core.h"
#include "error.h"
#include "fn.h"
#include "value.h"
#include <cstdint>
#include <stdexcept>

// Compiler Use ///////////////////////////////////////////////////////////////

Value __core__::apply_fn(Value fn, const Value args[], uint32_t n) {
  if (fn.is_fn()) {
    Fn f = *fn.as_fn();
    try {
      return f(args, n);
    } catch (std::out_of_range e) {
      throw ArityError(f.get_name(), f.get_arity(), n);
    }
  } else {
    // TODO might be better with a custom error to indicate that the first arg
    // of a function application was not a function specifically.
    throw InvalidArgError("function application", "Function", fn.type_string(),
                          0, fn);
  }
}

// Arithmetic /////////////////////////////////////////////////////////////////

// Core function for +
Value __core__::sum(const Value args[], uint32_t n) {
  // Keep checks and conversions to a minimum to allow faster computation.
  int64_t x = 0;
  double y = 0;
  bool is_double = false;

  for (uint32_t i = 0; i < n; ++i) {
    switch (args[i].get_type()) {
    case ValType::Flt:
      if (!is_double) {
        is_double = true;
        y = double(x);
      }
      y = y + args[i].as_flt();
      break;
    case ValType::Int:
      if (is_double) {
        y = y + args[i].as_int();
      } else {
        x = x + args[i].as_int();
      }
      break;
    default:
      throw InvalidArgError("+", "Number", args[i].type_string(), i, args[i]);
    }
  }

  return is_double ? Value(y) : Value::Int(x);
}

// Comparisson ////////////////////////////////////////////////////////////////

// Core function for =
// Uses value operator== for deep equality
Value __core__::equal(const Value args[], uint32_t n) {
  if (n == 1)
    return Value::True();

  for (uint32_t i = 0; i < n - 1; ++i) {
    if (!(args[i] == args[i + 1]))
      return Value::False();
  }
  return Value::True();
}
