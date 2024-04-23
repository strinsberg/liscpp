#ifndef LISCPP_CORE_H
#define LISCPP_CORE_H

#include "value.h"
#include "fn.h"

/* Core functions and values for lscpp that are not compiler macros
 *
 * There is a __core__ namespace to allow public use of functions and values
 * in compiled code, but to keep them from clashing with names used by the
 * user. The core functions and values used by the user are not wrapped in
 * a namespace or a module because we want to compile them using the same
 * symbols a user types without qualifiers. User typed symbols for modules
 * will have specific properties and resolve to module value lookups.
 *
 * NOTE that naming will follow what we expect the mangled names to be for
 * lscpp characters. I.e. + -> _plus_ and ? -> _qmark_ etc.
 */

namespace __core__ {

// for the compiler
Value apply_fn(Value, const Value args[], uint32_t n);

// internal functions for function values
Value sum(const Value args[], uint32_t n);
Value equal(const Value args[], uint32_t n);

} // namespace __core__

// Arithmetic /////////////////////////////////////////////////////////////////

const Value _plus_ = Value(new Fn("+", 0, __core__::sum));
const Value _equal_ = Value(new Fn("=", 1, __core__::equal));

#endif
