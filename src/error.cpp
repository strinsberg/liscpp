#include "fn.h"
#include "error.h"
#include "value.h"

Error::Error(const std::string &message, Value data)
      : m_message{message}, m_data{data} {}

const char *Error::what() const throw() {
  return m_message.c_str(); // TODO also some rep of data
}
