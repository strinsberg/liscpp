#ifndef LISCPP_ERROR_H
#define LISCPP_ERROR_H

#include "value.h"
#include <exception>
#include <stdexcept>
#include <string>

// TODO we might need some error types? or the error needs to hold a keyword
// or something to identify the type for the user.
class Error : public std::exception {
public:
  Error(const std::string &message, Value data);
  const char *what() const throw();

private:
  std::string m_message;
  Value m_data;
};

#endif
