#include "stream.h"
#include "error.h"
#include "type.h"
#include "value.h"
#include <format>
#include <stdexcept>

// NOTE I am not handling user errors in here, so any caller needs to handle
// possible file errors to return useful errors to the user. If a C++ error is
// encountered it is a library error and not a liscpp runtime error.

Stream::Stream(const std::string &filename, StreamType type)
    : m_type{type}, m_stream{&std::cout} {
  if (type == StreamType::InFile) {
    auto ifs = new std::ifstream();
    ifs->open(filename);
    m_stream = StreamUnion(ifs);
  } else if (type == StreamType::OutFile) {
    auto ofs = new std::ofstream();
    ofs->open(filename);
    m_stream = StreamUnion(ofs);
  } else {
    std::invalid_argument(std::format(
        "file stream must be created with InFile or OutFile: Got {}",
        type::str(type)));
  }
}

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
  default:
    throw std::invalid_argument(std::format(
        "Stream::is_open encountered uncovered type: Got type (as int) {}",
        int(m_type)));
  }
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
  default:
    throw std::invalid_argument(std::format(
        "Stream::is_eof encountered uncovered type: Got type (as int) {}",
        int(m_type)));
  }
}

void Stream::close() {
  if (m_type == StreamType::InFile) {
    m_stream.ifs->close();
  } else if (m_type == StreamType::OutFile) {
    m_stream.ofs->close();
  }
}

std::string *Stream::get_line() {
  std::string *str = new std::string();
  switch (m_type) {
  case StreamType::Input:
    std::getline(*m_stream.is, *str);
    return str;
  case StreamType::InFile:
    std::getline(*m_stream.ifs, *str);
    return str;
  default:
    throw std::invalid_argument(
        std::format("invalid stream for Stream::get_line: Got {}",
                    type::str(this->m_type)));
  }
}
