#ifndef LISCPP_ERROR_H
#define LISCPP_ERROR_H

#include "value.h"
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <string>

// Base generic error for liscpp exceptions and use errors.
class Error : public std::exception {
public:
  Error(const std::string &message, Value data,
        Value type = Value::new_keyword(":error"));
  virtual ~Error(){};
  const char *what() const throw();
  inline Value get_type() const { return m_type; }
  inline Value get_data() const { return m_data; }
  bool operator==(const Error &other) const;

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

class IoError : public Error {
public:
  IoError(const std::string &message, Value data);
};

class FileError : public Error {
public:
  FileError(const std::string &filename, const std::string &operation,
            const std::string &what);
};

#endif
