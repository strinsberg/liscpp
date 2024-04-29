#ifndef LISCPP_REP_H
#define LISCPP_REP_H

#include "type.h"
#include <cstdint>

namespace liscpp {

class Rep {
public:
  virtual void code_rep(std::ostream &) const = 0;
  virtual void display_rep(std::ostream &) const = 0;
};

} // namespace liscpp

#endif
