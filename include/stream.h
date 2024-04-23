#ifndef LISCPP_STREAM_H
#define LISCPP_STREAM_H

#include "value.h"
#include <fstream>
#include <iostream>

// This should probably be an interface with derived classes for each stream
// rather than a class with a union. Though each subclass would just wrap
// a stream anyway.

enum class StreamType { In, Out, Ifile, Ofile };

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
  Stream(std::istream *in) : m_type{StreamType::In}, m_stream{in} {}
  Stream(std::ostream *out) : m_type{StreamType::Out}, m_stream{out} {}
  Stream(std::istream &is) : m_type{StreamType::In}, m_stream{&is} {}
  Stream(std::ostream &os) : m_type{StreamType::In}, m_stream{&os} {}

  Stream(std::ifstream *in) : m_type{StreamType::Ifile}, m_stream{in} {}
  Stream(std::ofstream *out) : m_type{StreamType::Ofile}, m_stream{out} {}
  Stream(const std::string &filename, StreamType type);
  ~Stream();

  std::string type_string();
  bool is_open();
  bool is_eof();
  void close();
  std::string *get_line();

private:
  StreamType m_type;
  StreamUnion m_stream;
};

#endif
