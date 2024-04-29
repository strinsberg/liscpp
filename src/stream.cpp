#include "stream.h"
#include "error.h"
#include "type.h"
#include "value.h"

using namespace liscpp;

Stream::~Stream() { close(); }

bool Stream::is_open() {
  switch (m_type) {
  case StreamType::Input:
  case StreamType::Output:
    return true;
  case StreamType::InFile:
    return m_stream.ifs->is_open();
  case StreamType::OutFile:
    return m_stream.ofs->is_open();
  }
  return false;
}

bool Stream::is_eof() {
  switch (m_type) {
  case StreamType::Input:
    return m_stream.is->eof();
  case StreamType::Output:
    return m_stream.os->eof();
  case StreamType::InFile:
    return m_stream.ifs->eof();
  case StreamType::OutFile:
    return m_stream.ofs->eof();
  }
  return true;
}

void Stream::close() {
  if (m_type == StreamType::InFile) {
    m_stream.ifs->close();
  } else if (m_type == StreamType::OutFile) {
    m_stream.ofs->close();
  }
}

GcString *Stream::get_line() {
  GcString *str = new GcString();
  switch (m_type) {
  case StreamType::Input:
    std::getline(*m_stream.is, *str);
    return str;
  case StreamType::InFile:
    std::getline(*m_stream.ifs, *str);
    return str;
  default:
    throw __error__::new_io_error(
        new GcString("cannot get line from an output stream"), Value(this));
  }
}

void Stream::code_rep(std::ostream &os) const {
  // TODO would be fun to be able to see the position and number of bytes
  os << "#<Stream: " << __type__::str(m_type) << ">";
}

void Stream::display_rep(std::ostream &os) const { code_rep(os); }

// Stream functions ///////////////////////////////////////////////////////////

Stream *__stream__::new_ifstream(GcString *filename) {
  try {
    auto ifs = new std::ifstream(filename->c_str());
    ifs->exceptions(std::ifstream::failbit | std::ifstream::badbit);
    return new Stream(ifs);
  } catch (...) {
    throw __error__::new_file_error(filename, FileOp::Open);
  }
}

Stream *__stream__::new_ofstream(GcString *filename) {
  try {
    auto ifs = new std::ifstream(filename->c_str());
    ifs->exceptions(std::ifstream::failbit | std::ifstream::badbit);
    return new Stream(ifs);
  } catch (...) {
    throw __error__::new_file_error(filename, FileOp::Open);
  }
}
