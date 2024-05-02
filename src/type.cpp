#include "type.h"
#include "value.h"
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace liscpp;

GcString __type__::str(ValueType t) {
  switch (t) {
  case ValueType::Nil:
    return "#t:nil";
  case ValueType::Bool:
    return "#t:bool";
  case ValueType::Char:
    return "#t:char";
  case ValueType::Int:
    return "#t:int";
  case ValueType::Float:
    return "#t:float";
  case ValueType::Symbol:
    return "#t:symbol";
  case ValueType::Keyword:
    return "#t:keyword";
  case ValueType::String:
    return "#t:string";
  case ValueType::List:
    return "#t:list";
  case ValueType::Vector:
    return "#t:vector";
  case ValueType::Map:
    return "#t:map";
  case ValueType::Generator:
    return "#t:generator";
  case ValueType::Fn:
    return "#t:function";
  case ValueType::Stream:
    return "#t:stream";
  case ValueType::Error:
    return "#t:error";
  }
  return "**UNCOVERED-TYPE**";
}

GcString __type__::str(FnType t) {
  switch (t) {
  case FnType::Fn0:
    return "#t:function-fn0";
  case FnType::Fn1:
    return "#t:function-fn1";
  case FnType::Fn2:
    return "#t:function-fn2";
  case FnType::Fn3:
    return "#t:function-fn3";
  case FnType::Fn4:
    return "#t:function-fn4";
  case FnType::Fn5:
    return "#t:function-fn5";
  case FnType::FnAny:
    return "#t:function-fn-any";
  case FnType::Closure:
    return "#t:function-closure";
  }
  return "**UNCOVERED-TYPE**";
}

GcString __type__::str(StreamType t) {
  switch (t) {
  case StreamType::Input:
    return "#t:stream-input";
  case StreamType::Output:
    return "#t:stream-output";
  case StreamType::InFile:
    return "#t:stream-ifile";
  case StreamType::OutFile:
    return "#t:stream-ofile";
  }
  return "**UNCOVERED-TYPE**";
}

GcString __type__::str(FileOp t) {
  switch (t) {
  case FileOp::Open:
    return "#t:fileop-open";
  case FileOp::Close:
    return "#t:fileop-close";
  case FileOp::Read:
    return "#t:fileop-read";
  case FileOp::Write:
    return "#t:fileop-write";
  }
  return "**UNCOVERED-TYPE**";
}

GcString __type__::str(ErrorType t) {
  switch (t) {
  case ErrorType::Error:
    return "#t:error-base";
  case ErrorType::Arity:
    return "#t:error-arity";
  case ErrorType::InvalidArg:
    return "#t:error-invalid-argument";
  case ErrorType::OutOfBounds:
    return "#t:error-out-of-bounds";
  case ErrorType::File:
    return "#t:error-file";
  case ErrorType::IO:
    return "#t:error-io";
  case ErrorType::Panic:
    return "#t:error-panic";
  }
  return "**UNCOVERED-TYPE**";
}

// Representations ////////////////////////////////////////////////////////////
const char ASCII_START = 33;
const char ASCII_END = 126;

void __type__::code_rep(std::ostream &os, const char &ch) {
  switch (ch) {
  case '\0':
    os << "\\null";
    break;
  case '\t':
    os << "\\tab";
    break;
  case '\n':
    os << "\\newline";
    break;
  case ' ':
    os << "\\space";
    break;
  default:
    if (ch < ASCII_START or ch > ASCII_END) {
      os << "\\x" << std::setw(2) << std::setfill('0') << std::hex
         << (0xFF & ch);
    } else {
      os << "\\" << ch;
    }
  }
}

void __type__::code_rep(std::ostream &os, const GcString &s) {
  // TODO this will not fully escape the string, it will print quotes around it
  // and escape internal quotes.
  os << std::quoted(s);
}

void __type__::code_rep(std::ostream &os, const GcVector &v) {
  os << "[";
  if (v.size() > 0) {
    for (auto it = v.begin(); it != v.end() - 1; ++it) {
      (*it).code_rep(os);
      os << " ";
    }
    v.back().code_rep(os);
  }
  os << "]";
}

void __type__::code_rep(std::ostream &os, const GcMap &m) {
  os << "{";
  uint32_t i = 0;
  for (auto it = m.begin(); it != m.end(); ++it) {
    it->first.code_rep(os);
    os << " ";
    it->second.code_rep(os);
    if (i < m.size() - 1)
      os << " ";
    i++;
  }
  os << "}";
}

void __type__::display_rep(std::ostream &os, const GcVector &v) {
  os << "[";
  if (v.size() > 0) {
    for (auto it = v.begin(); it != v.end() - 1; ++it) {
      (*it).display_rep(os);
      os << " ";
    }
    v.back().display_rep(os);
  }
  os << "]";
}

void __type__::display_rep(std::ostream &os, const GcMap &m) {
  os << "{";
  uint32_t i = 0;
  for (auto it = m.begin(); it != m.end(); ++it) {
    it->first.display_rep(os);
    os << " ";
    it->second.display_rep(os);
    if (i < m.size() - 1)
      os << " ";
    i++;
  }
  os << "}";
}

// Overload ostream ///////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const liscpp::GcString &s) {
  // NOTE since this is the operator that outputs GcString
  // you cannot pass the parameter s or it will infinite loop.
  os << s.c_str();
  return os;
}

std::ostream &operator<<(std::ostream &os, const liscpp::GcVector &v) {
  __type__::display_rep(os, v);
  return os;
}

std::ostream &operator<<(std::ostream &os, const liscpp::GcMap &m) {
  __type__::display_rep(os, m);
  return os;
}

std::ostream &operator<<(std::ostream &os, const ValueType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &operator<<(std::ostream &os, const FnType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &operator<<(std::ostream &os, const StreamType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &operator<<(std::ostream &os, const ErrorType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &operator<<(std::ostream &os, const FileOp &type) {
  os << __type__::str(type);
  return os;
}
