#ifndef LISCPP_CORE_NS_H
#define LISCPP_CORE_NS_H

#include "fn.h"
#include "value.h"
#include "value_functions.h"

namespace liscpp {

namespace __core__ {

// util //
Value call(Fn *, const Value[], uint32_t);

// Arithmetic //
Value sum(const Value[], uint32_t);
Value sub(const Value[], uint32_t);
Value product(const Value[], uint32_t);
Value divide(const Value[], uint32_t);
Value int_div(const Value[], uint32_t);
Value modulo(const Value[], uint32_t);

} // namespace __core__

namespace core {

// Arithmetic //
const Value _plus_ =
    __value__::new_fn(new Fn(new GcString("core/+"), 0, liscpp::__core__::sum));
const Value _minus_ =
    __value__::new_fn(new Fn(new GcString("core/-"), 1, liscpp::__core__::sub));
const Value _star_ = __value__::new_fn(
    new Fn(new GcString("core/*"), 0, liscpp::__core__::product));
const Value _fslash_ = __value__::new_fn(
    new Fn(new GcString("core//"), 1, liscpp::__core__::divide));
const Value _fslash__fslash_ = __value__::new_fn(
    new Fn(new GcString("core///"), 1, liscpp::__core__::int_div));
const Value _percent_ = __value__::new_fn(
    new Fn(new GcString("core/%"), 2, liscpp::__core__::modulo));

} // namespace core

} // namespace liscpp

#endif
