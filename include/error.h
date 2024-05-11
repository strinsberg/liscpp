#ifndef LISCPP_ERROR_H
#define LISCPP_ERROR_H

#include "rep.h"
#include "type.h"
#include "value.h"
#include <cstdint>
#include <exception>

namespace liscpp {

class Error : public std::exception, public Rep {
public:
  Error(GcString *message, ErrorType type, Value data);

  // Accessors
  inline ErrorType get_type() const { return m_type; }
  inline Value get_data() const { return m_data; }

  // Overrides
  const char *what() const throw() override;

  // Overloads
  bool operator==(const Error &) const;

  // Representation
  void code_rep(std::ostream &) const override;
  void display_rep(std::ostream &) const override;

private:
  GcString *m_message;
  ErrorType m_type;
  Value m_data;
};

// Error Functions //

namespace __error__ {

Error *new_arity_error(GcString *where, uint32_t expected, uint32_t actual);
Error *new_invalid_arg_error(GcString *where, uint32_t pos, ValueType expected,
                             ValueType actual);
Error *new_invalid_arg_error(GcString *where, uint32_t pos, ValueType expected,
                             ValueType actual);
Error *new_file_error(GcString *where, FileOp type);
Error *new_io_error(GcString *where, Value stream);

} // namespace __error__

} // namespace liscpp

#endif
