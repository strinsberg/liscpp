#include "type.h"
#include "util.h"
#include "value.h"
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace liscpp;

// GcMapValueCompare //////////////////////////////////////////////////////////

// This is a lot of code for something very simple, but it gives a consistent
// comparisson for values in GcMap that are not equal. It should also be
// consistent comp(a, b) and comp(b, a).
// In code < will only work with numerical values, but this can also be used
// for some kind of default sort for collections that might contain different
// types. Though it might be good to template this or something like it to
// allow for custom comparators for sort, but that might actually be better
// using some other interface altogether, so that a user does not have to
// specify relationships between types.

bool GcMapValueCompare::operator()(const Value &a, const Value &b) const {
  switch (a.get_type()) {
  case ValueType::Nil:
    if (b.is_nil()) {
      return false;
    }
    return true;
  case ValueType::Bool:
    return compare_bool(a.as_bool(), b);
  case ValueType::Char:
    return compare_char(a.as_char(), b);
  case ValueType::Int:
    return compare_int(a.as_int(), b);
  case ValueType::Float:
    return compare_float(a.as_float(), b);
  case ValueType::Keyword:
    return compare_keyword(a.as_keyword(), b);
  case ValueType::Symbol:
    return compare_symbol(a.as_symbol(), b);
  case ValueType::String:
    return compare_string(a.as_string(), b);
  case ValueType::List:
    return compare_list(a.as_list(), b);
  case ValueType::Vector:
    return compare_vector(a.as_vector(), b);
  case ValueType::Map:
    return compare_map(a.as_map(), b);
  case ValueType::Generator:
    return compare_generator(a.as_generator(), b);
  case ValueType::Fn:
    return compare_fn(a.as_fn(), b);
  case ValueType::Stream:
    return compare_stream(a.as_stream(), b);
  case ValueType::Error:
    return compare_error(a.as_error(), b);
  }
  util::panic("uncovered type in GcMapCompare::operator()");
  return false; // unreachable
}

bool GcMapValueCompare::compare_bool(bool a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Bool:
    return a < b.as_bool();
  case ValueType::Nil:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_char(char a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Char:
    return a < b.as_char();
  case ValueType::Nil:
  case ValueType::Bool:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_int(int64_t a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Int:
    return a < b.as_int();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_float(double a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Float:
    return a < b.as_float();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_keyword(GcString *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Keyword:
    return *a < *b.as_keyword();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_symbol(GcString *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Symbol:
    return *a < *b.as_symbol();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_string(GcString *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::String:
    return *a < *b.as_string();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_list(List *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::List:
    return a < b.as_list();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
  case ValueType::String:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_vector(GcVector *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Vector:
    return a < b.as_vector();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
  case ValueType::String:
  case ValueType::List:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_map(GcMap *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Map:
    return a < b.as_map();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
  case ValueType::String:
  case ValueType::List:
  case ValueType::Vector:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_generator(Generator *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Generator:
    return a < b.as_generator();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
  case ValueType::String:
  case ValueType::List:
  case ValueType::Vector:
  case ValueType::Map:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_fn(Fn *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Fn:
    return a < b.as_fn();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
  case ValueType::String:
  case ValueType::List:
  case ValueType::Vector:
  case ValueType::Map:
  case ValueType::Generator:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_stream(Stream *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Stream:
    return a < b.as_stream();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
  case ValueType::String:
  case ValueType::List:
  case ValueType::Vector:
  case ValueType::Map:
  case ValueType::Generator:
  case ValueType::Fn:
    return false;
  default:
    return true;
  }
}

bool GcMapValueCompare::compare_error(Error *a, const Value &b) const {
  switch (b.get_type()) {
  case ValueType::Error:
    return a < b.as_error();
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Char:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Keyword:
  case ValueType::Symbol:
  case ValueType::String:
  case ValueType::List:
  case ValueType::Vector:
  case ValueType::Map:
  case ValueType::Generator:
  case ValueType::Fn:
  case ValueType::Stream:
    return false;
  default:
    return true;
  }
}

// Overload ostream ///////////////////////////////////////////////////////////

std::ostream &liscpp::operator<<(std::ostream &os, const liscpp::GcString &s) {
  // NOTE since this is the operator that outputs GcString
  // you cannot pass the parameter s or it will infinite loop.
  os << s.c_str();
  return os;
}

std::ostream &liscpp::operator<<(std::ostream &os, const liscpp::GcVector &v) {
  __type__::display_rep(os, v);
  return os;
}

std::ostream &liscpp::operator<<(std::ostream &os, const liscpp::GcMap &m) {
  __type__::display_rep(os, m);
  return os;
}

std::ostream &liscpp::operator<<(std::ostream &os, const ValueType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &liscpp::operator<<(std::ostream &os, const FnType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &liscpp::operator<<(std::ostream &os, const StreamType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &liscpp::operator<<(std::ostream &os, const ErrorType &type) {
  os << __type__::str(type);
  return os;
}

std::ostream &liscpp::operator<<(std::ostream &os, const FileOp &type) {
  os << __type__::str(type);
  return os;
}

// type functions /////////////////////////////////////////////////////////////

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
  case ValueType::Number:
    return "#t:number";
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

