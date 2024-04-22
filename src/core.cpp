#include "core.h"
#include "error.h"
#include "fn.h"
#include "value.h"
#include <cstdint>

// Compiler Use ///////////////////////////////////////////////////////////////

Value __core__::apply_fn(Value fn, const Value args[], uint32_t n) {
  if (fn.is_fn()) {
    Fn f = *fn.as_fn();
    return f(args, n);
  } else {
    throw Error("cannot apply as a function", fn); // TODO fix using value rep
  }
}

// Arithmetic /////////////////////////////////////////////////////////////////

Value __core__::sum(const Value args[], uint32_t n) {
  // Keep checks and conversions to a minimum to allow faster computation.
  int64_t x = 0;
  double y = 0;
  bool is_double = false;

  for (uint32_t i = 0; i < n; ++i) {
    if (args[i].is_flt()) {
      if (!is_double) {
        is_double = true;
        y = double(x);
      }
      y = y + args[i].as_flt();

    } else if (args[i].is_int()) {
      if (is_double) {
        y = y + args[i].as_int();
      } else {
        x = x + args[i].as_int();
      }

    } else {
      throw Error("arguments to sum must be numbers", args[i]);
    }
  }

  return is_double ? Value(y) : Value::Int(x);
}

// Comparisson ////////////////////////////////////////////////////////////////

Value __core__::equal(const Value args[], uint32_t n) {
  if (n == 0)
    return Value::False();
  else if (n == 1)
    return Value::True();

  for (uint32_t i = 0; i < n - 1; ++i) {
    if (!(args[i] == args[i + 1]))
      return Value::False();
  }
  return Value::True();
}
