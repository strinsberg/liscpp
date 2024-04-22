#ifndef LISCPP_ERROR_H
#define LISCPP_ERROR_H

#include "value.h"
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <string>

// This is an error that should crash a program and should not be able to be
// caught by a user. Not entirely sure how to represent that yet, or if there
// should be a separate type for me to indicate errors in compiled or lib code
// and for a user to indicate a fatal unrecoverable error.
class Panic : public std::exception {
public:
  Panic(const std::string &message) : m_message(message) {}
  const char *what() const throw() { return m_message.c_str(); }

protected:
  std::string m_message;
};

// Base generic error for liscpp exceptions and use errors.
class Error : public std::exception {
public:
  Error(const std::string &message, Value data,
        Value type = Value::Key(":error"));
  virtual ~Error(){};
  const char *what() const throw();
  bool operator==(const Error& other) const;

protected:
  std::string m_message;
  Value m_type;
  Value m_data;
};

class ArityError : public Error {
public:
  ArityError(const std::string &fn_name, uint32_t expected, uint32_t given);
};

class InvalidArgError : public Error {
public:
  InvalidArgError(const std::string &fn_name, const std::string &expected,
                  const std::string &given, uint32_t pos, Value data);
};

#endif
