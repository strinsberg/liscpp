#ifndef LISCPP_ERROR_H
#define LISCPP_ERROR_H

#include "value.h"
#include <exception>
#include <stdexcept>
#include <string>

// TODO I think that I might want to create some other error types, but have
// them all hold information that will be useful for the user like in clojure.
// So each error can have an genuine type and hold a keyword for the type name
// that is provided by the constructor. We can give core functions for users
// to construct them and a custom type that takes a value for that type as
// a keyword. Then there should be a message and a slot for data. These should
// all be accessible with core functions for the user to be able to access them
// and also be part of the representation of the errors when they are printed
// or error statements are given. Errors need to be as clear as posible at
// runtime so that it is easy to pick up where the problem was, but also it
// would be really nice if there was a way to indicate what line of the source
// code an error was caused on. Perhaps that would mean passing line
// information on to apply for evey call. Then some kind of call stack could be
// represented when errors are thrown. Even if C++ gave really detailed error
// Information we don't really want user errors at runtime to reference
// compiled code, but to reference the source code. Though I suppose runtime
// errors usually don't reference source code line numbers, that is for compiler
// errors to do and then to try and catch as much as possible at compile time.
// However, for function application etc. that is either not possible or
// requires a lot of tracing during compile time to designate the types of every
// variable and the types of variables in function argument lists.

class Error : public std::exception {
public:
  Error(const std::string &message, Value data);
  const char *what() const throw();

private:
  std::string m_message;
  Value m_data;
};

#endif
