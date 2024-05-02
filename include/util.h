#ifndef LISCPP_UTIL_H
#define LISCPP_UTIL_H

#include "type.h"

namespace util {

class Error : public std::exception {
public:
  Error(liscpp::GcString *message);

  // Overrides
  const char *what() const throw() override;

private:
  liscpp::GcString *m_message;
};

void panic(const char *message);

} // namespace util

#endif
