#include "error.h"
#include "value.h"
#include <cstdint>
#include <format>

Error::Error(const std::string &message, Value data, Value type)
    : m_message{new GcString(message)}, m_type{type}, m_data{data} {
  if (not m_type.is_keyword())
    throw InvalidArgError(GcString("error"), GcString("Keyword"),
                          GcString(type::str(m_type.get_type())), 2, m_type);
}

const char *Error::what() const throw() {
  return m_message->c_str(); // TODO also some rep of data
}

bool Error::operator==(const Error &other) const {
  return m_type == other.m_type and m_message == other.m_message and
         m_data == other.m_data;
}

ArityError::ArityError(const GcString &fn_name, uint32_t expected,
                       uint32_t given)
    : Error(std::format("Arity Error: {} expects at least {} args: Got {}",
                        fn_name, expected, given),
            Value::new_keyword(new GcString(":arity")), Value()) {}

InvalidArgError::InvalidArgError(const GcString &fn_name,
                                 const GcString &expected,
                                 const GcString &given, uint32_t pos,
                                 Value data)
    : Error(std::format(
                "Invalid Argument Error: {} expects {} at position {}: Got {}",
                fn_name, pos, expected, given),
            Value::new_keyword(new GcString(":invalid-argument")), data) {}

FileError::FileError(const GcString &filename, const GcString &operation,
                     const GcString &what)
    : Error(std::format("File Error: error {} file \"{}\": {}", filename,
                        operation, what),
            Value::new_keyword(new GcString(":file")), Value()) {}

IoError::IoError(const GcString &message, Value stream)
    : Error(std::format("Io Error: {}", message),
            Value::new_keyword(new GcString(":io")), stream) {}
