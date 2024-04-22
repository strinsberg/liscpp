#include "error.h"
#include "value.h"
#include <cstdint>
#include <format>

Error::Error(const std::string &message, Value data, Value type)
    : m_message{message}, m_type{type}, m_data{data} {
  if (not m_type.is_key())
    throw InvalidArgError("error", "Keyword", m_type.type_string(), 2, m_type);
}

const char *Error::what() const throw() {
  return m_message.c_str(); // TODO also some rep of data
}

ArityError::ArityError(const std::string &fn_name, uint32_t expected,
                       uint32_t given)
    : Error(std::format("Arity Error: {} expects at least {} args: Got {}",
                        fn_name, expected, given),
            Value::Key(":arity"), Value()) {}

InvalidArgError::InvalidArgError(const std::string &fn_name,
                                 const std::string &expected,
                                 const std::string &given, uint32_t pos,
                                 Value data)
    : Error(std::format(
                "Invalid Argument Error: {} expects {} at position {}: Got {}",
                fn_name, pos, expected, given),
            Value::Key(":invalid-argument"), data) {}
