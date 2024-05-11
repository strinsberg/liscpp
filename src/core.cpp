#include "core.h"
#include "error.h"
#include "value.h"

using namespace liscpp;

// Util ///////////////////////////////////////////////////////////////////////
Value liscpp::__core__::call(Fn *f, const Value args[], uint32_t arity) {
  return (*f)(args, arity);
}

// Arithmetic /////////////////////////////////////////////////////////////////

Value liscpp::__core__::sum(const Value args[], uint32_t n) {
  // Keep checks and conversions to a minimum to allow faster computation.
  int64_t x = 0;
  double y = 0;
  bool is_double = false;

  for (uint32_t i = 0; i < n; ++i) {
    switch (args[i].get_type()) {
    case ValueType::Float:
      if (!is_double) {
        is_double = true;
        y = double(x);
      }
      y = y + args[i].as_float();
      break;
    case ValueType::Int:
      if (is_double) {
        y = y + args[i].as_int();
      } else {
        x = x + args[i].as_int();
      }
      break;
    default:
      throw __error__::new_invalid_arg_error(
          new GcString("core/+"), i, ValueType::Number, args[i].get_type());
    }
  }

  if (is_double) {
    return Value(y);
  } else {
    return Value(x);
  }
}

Value liscpp::__core__::sub(const Value[], uint32_t) { return Value(); }

Value liscpp::__core__::product(const Value args[], uint32_t n) {
  int64_t x = 1;
  double y = 1.0;
  bool is_double = false;

  for (uint32_t i = 0; i < n; ++i) {
    switch (args[i].get_type()) {
    case ValueType::Float:
      if (!is_double) {
        is_double = true;
        y = double(x);
      }
      y = y * args[i].as_float();
      break;
    case ValueType::Int:
      if (is_double) {
        y = y * args[i].as_int();
      } else {
        x = x * args[i].as_int();
      }
      break;
    default:
      throw __error__::new_invalid_arg_error(
          new GcString("core/*"), i, ValueType::Number, args[i].get_type());
    }
  }

  if (is_double) {
    return Value(y);
  } else {
    return Value(x);
  }
}

Value liscpp::__core__::divide(const Value[], uint32_t) { return Value(); }

Value liscpp::__core__::int_div(const Value[], uint32_t) { return Value(); }

Value liscpp::__core__::modulo(const Value[], uint32_t) { return Value(); }
