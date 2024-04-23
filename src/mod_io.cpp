#include "mod_io.h"
#include "stream.h"
#include <error.h>

ModIo *ModIo::m_mod = nullptr;

ModIo *ModIo::require() {
  if (m_mod == nullptr) {
    m_mod = new ModIo();
    m_mod->init();
  }
  return m_mod;
}

// This is where we create the structures necessary for the module fields
// and populate them as well as run any top level free code. Library modules
// will not have free code, but since clojure and other languages allow
// code to be written outside of functions that code would be executed on
// the first require inside this function.
void ModIo::init() {
  getline = Value(__mod_io__::getline);
}

// Function definitions ///////////////////////////////////////////////////////

Value __mod_io__::getline(Value stream) {
  if (stream.is_strm()) {
    Stream *s = stream.as_strm();
    if (!s->is_open() or s->is_eof()) {
      return Value();
    }
    return Value(s->get_line());
  }
  throw InvalidArgError("core.io/getline", "Stream", stream.type_string(), 0,
                        stream);
}
