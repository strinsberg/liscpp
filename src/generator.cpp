#include "generator.h"
#include "fn.h"
#include "type.h"
#include "value.h"

using namespace liscpp;

Generator::Generator(Fn *next, Fn *is_done)
    : m_fn_next{next}, m_fn_is_done{is_done} {
  if (next->get_arity() > 0) {
    // throw __error__::new_arity_error(
    //     new GcString("Generator::Generator is_done"), 0, next->get_arity());
  } else if (is_done->get_arity() > 0) {
    // throw __error__::new_arity_error(
    //     new GcString("Generator::Generator is_done"), 0, next->get_arity());
  }
}

Value Generator::next() {
  Value args[0];
  return (*m_fn_next)(args, 0);
}

bool Generator::is_done() {
  Value args[0];
  return (*m_fn_is_done)(args, 0).is_truthy();
}

// Representation
void Generator::code_rep(std::ostream &os) const { os << "#<Generator>"; }

void Generator::display_rep(std::ostream &os) const { code_rep(os); }
