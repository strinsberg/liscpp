#include "error.h"
#include "type.h"
#include "value.h"
#include "value_functions.h"
#include <cstdint>
#include <iostream>

using namespace liscpp;

Error::Error(GcString *message, ErrorType type, Value data)
    : m_message{message}, m_type{type}, m_data{data} {}

// Error Class Methods //

const char *Error::what() const throw() { return m_message->c_str(); }

bool Error::operator==(const Error &other) const {
  return *m_message == *other.m_message and m_data == other.m_data and
         m_type == other.m_type;
}

void Error::code_rep(std::ostream &os) const {
  os << "#<Error " << m_type << ">";
}

void Error::display_rep(std::ostream &os) const { os << *m_message; }

// Error Functions ////////////////////////////////////////////////////////////

Error *__error__::new_arity_error(GcString *where, uint32_t expected,
                                  uint32_t actual) {
  GcOsStream oss;
  oss << "Arity Error: " << where << " expects at least " << expected
      << " args: Got " << actual;
  return new Error(new GcString(oss.str()), ErrorType::Arity, Value());
}

Error *__error__::new_invalid_arg_error(GcString *where, uint32_t pos,
                                        ValueType expected, ValueType actual) {
  GcOsStream oss;
  oss << "Invalid Argument Error: " << where << " expects argument #" << pos
      << " to be of type " << expected << ": Got " << actual;
  return new Error(new GcString(oss.str()), ErrorType::InvalidArg, Value());
}

Error *__error__::new_file_error(GcString *where, FileOp type) {
  GcOsStream oss;
  oss << "File Error: operation " << type << " failed: '" << where << "'";
  return new Error(new GcString(oss.str()), ErrorType::File,
                   __value__::new_string(where));
}

Error *__error__::new_io_error(GcString *where, Value stream) {
  GcOsStream oss;
  oss << "Io Error: " << where << ": " << stream;
  return new Error(new GcString(oss.str()), ErrorType::IO, stream);
}
