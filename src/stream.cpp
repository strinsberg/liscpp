#include "stream.h"
#include "error.h"
#include "value.h"
#include <format>

Stream::Stream(const std::string &filename, StreamType type)
    : m_type{type}, m_stream{&std::cout} {
  if (type == StreamType::Ifile) {
    auto ifs = new std::ifstream();
    try {
      ifs->open(filename);
      m_stream = StreamUnion(ifs);
    } catch (std::exception e) {
      throw FileError(filename, "opening", e.what());
    }
  } else if (type == StreamType::Ofile) {
    auto ofs = new std::ofstream();
    try {
      ofs->open(filename);
      m_stream = StreamUnion(ofs);
    } catch (std::exception e) {
      throw FileError(filename, "opening", e.what());
    }
  } else {
    throw Panic(
        std::format("file stream must be of type Ifile or Ofile: Got {}",
                    this->type_string()));
  }
}

std::string Stream::type_string() {
  switch (m_type) {
  case StreamType::In:
    return "InputStream";
  case StreamType::Out:
    return "OutputStream";
  case StreamType::Ifile:
    return "InputFileStream";
  case StreamType::Ofile:
    return "OutputFileStream";
  }
  throw Panic(std::format("Stream::type_string encountered uncovered type {}",
                          int(m_type)));
}

bool Stream::is_open() {
  switch (m_type) {
  case StreamType::In:
  case StreamType::Out:
    return true;
  case StreamType::Ifile:
    return m_stream.ifs->is_open();
  case StreamType::Ofile:
    return m_stream.ofs->is_open();
  }
  throw Panic(std::format("Stream::is_open encountered uncovered type {}",
                          int(m_type)));
}

bool Stream::is_eof() {
  switch (m_type) {
  case StreamType::In:
    return m_stream.is->eof();
  case StreamType::Out:
    return m_stream.os->eof();
  case StreamType::Ifile:
    return m_stream.ifs->eof();
  case StreamType::Ofile:
    return m_stream.ofs->eof();
  }
  throw Panic(
      std::format("Stream::eof encountered uncovered type {}", int(m_type)));
}

void Stream::close() {
  if (m_type == StreamType::Ifile) {
    m_stream.ifs->close();
  } else if (m_type == StreamType::Ofile) {
    m_stream.ofs->close();
  }
}

std::string *Stream::get_line() {
  // TODO This will make this slow, though not as bad as get_ch
  // might be better to use try catch and throw errors if the read fails
  if (!is_open()) {
    throw IoError("cannot get line from closed stream", Value(this));
  } else if (is_eof()) {
    throw IoError("cannot get line from stream eof", Value(this));
  }

  std::string *str = new std::string();
  switch (m_type) {
  case StreamType::In:
    std::getline(*m_stream.is, *str);
    return str;
  case StreamType::Ifile:
    std::getline(*m_stream.ifs, *str);
    return str;
  default:
    throw IoError(std::format("cannot get line from an output stream: Got {}",
                              this->type_string()),
                  Value(this));
  }
}

Stream::~Stream() { close(); }
