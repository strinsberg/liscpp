#ifndef LISCPP_STREAM_H
#define LISCPP_STREAM_H

#include "type.h"
#include "value.h"
#include <fstream>
#include <iostream>

class Stream {
public:
  Stream(std::istream *in) : m_type{StreamType::Input}, m_stream{.is = in} {}
  Stream(std::ostream *out) : m_type{StreamType::Output}, m_stream{.os = out} {}
  Stream(std::istream &is) : m_type{StreamType::Input}, m_stream{.is = &is} {}
  Stream(std::ostream &os) : m_type{StreamType::Output}, m_stream{.os = &os} {}
  Stream(std::ifstream *in) : m_type{StreamType::InFile}, m_stream{.ifs = in} {}
  Stream(std::ofstream *out)
      : m_type{StreamType::OutFile}, m_stream{.ofs = out} {}
  Stream(const std::string &filename, StreamType type);
  ~Stream();

  StreamType get_type() { return m_type; }
  bool is_open();
  bool is_eof();
  void close();
  GcString *get_line();

private:
  StreamType m_type;
  union {
    std::istream *is;
    std::ostream *os;
    std::ifstream *ifs;
    std::ofstream *ofs;
  } m_stream;
};

#endif
