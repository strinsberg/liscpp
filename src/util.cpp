#include "util.h"
#include <iostream>

using namespace util;

Error::Error(liscpp::GcString *message) : m_message{message} {}

const char *Error::what() const throw() { return m_message->c_str(); }

void util::panic(const char *message) {
  std::cerr << message << std::endl;
  exit(-1);
}
