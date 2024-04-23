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

bool Error::operator==(const Error &other) const {
  return m_type == other.m_type and m_message == other.m_message and
         m_data == other.m_data;
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

FileError::FileError(const std::string &filename, const std::string &operation,
                     const std::string &what)
    : Error(std::format("File Error: error {} file \"{}\": {}", filename,
                        operation, what),
            Value::Key(":file"), Value()) {}

IoError::IoError(const std::string &message, Value stream)
    : Error(std::format("Io Error: {}", message), Value::Key(":io"), stream) {}
