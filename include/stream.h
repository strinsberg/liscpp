#ifndef LISCPP_STREAM_H
#define LISCPP_STREAM_H

#include "value.h"
#include "type.h"
#include <fstream>
#include <iostream>

// This should probably be an interface with derived classes for each stream
// rather than a class with a union. Though each subclass would just wrap
// a stream anyway.

union StreamUnion {
  StreamUnion(std::istream *is) : is{is} {}
  StreamUnion(std::ostream *os) : os{os} {}
  StreamUnion(std::ifstream *ifs) : ifs{ifs} {}
  StreamUnion(std::ofstream *ofs) : ofs{ofs} {}

  std::istream *is;
  std::ostream *os;
  std::ifstream *ifs;
  std::ofstream *ofs;
};

class Stream {
public:
  Stream(std::istream *in) : m_type{StreamType::Input}, m_stream{in} {}
  Stream(std::ostream *out) : m_type{StreamType::Output}, m_stream{out} {}
  Stream(std::istream &is) : m_type{StreamType::Input}, m_stream{&is} {}
  Stream(std::ostream &os) : m_type{StreamType::Output}, m_stream{&os} {}

  Stream(std::ifstream *in) : m_type{StreamType::InFile}, m_stream{in} {}
  Stream(std::ofstream *out) : m_type{StreamType::OutFile}, m_stream{out} {}
  Stream(const std::string &filename, StreamType type);
  ~Stream();

  bool is_open();
  bool is_eof();
  void close();
  std::string *get_line();

private:
  StreamType m_type;
  StreamUnion m_stream;
};

#endif
