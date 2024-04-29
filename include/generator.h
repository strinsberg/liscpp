#ifndef LISCPP_GENERATOR_H
#define LISCPP_GENERATOR_H

#include "fn.h"
#include "rep.h"
#include "type.h"

namespace liscpp {

class Generator : Rep {
public:
  Generator(Fn *next, Fn *is_done);
  virtual ~Generator() {}
  virtual Value next();
  virtual bool is_done();

  void code_rep(std::ostream &os) const override;
  void display_rep(std::ostream &os) const override;

private:
  Fn *m_fn_next;
  Fn *m_fn_is_done;
};

} // namespace liscpp

#endif
