#include "core.h"
#include "mod_io.h"
#include "stream.h"
#include "value.h"
#include <gtest/gtest.h>

TEST(ModIoGetline, does_it_read_a_line_from_a_stream) {
  std::istringstream iss("hello, world!\nwhat is your name?\n");
  Value stream(new Stream{iss});

  EXPECT_EQ(__mod_io__::getline(stream), Value::Str("hello, world!"));
  EXPECT_EQ(__mod_io__::getline(stream), Value::Str("what is your name?"));
  EXPECT_EQ(__mod_io__::getline(stream), Value::Str(""));
  EXPECT_EQ(__mod_io__::getline(stream), Value());
}

TEST(ModIoGetline, can_it_be_applied_to_read_a_line_from_a_stream) {
  std::istringstream iss("hello, world!\nwhat is your name?\nmine is greg!");
  Value stream(new Stream{iss});
  Value args[] = {stream};

  ModIo *mod = ModIo::require();

  EXPECT_EQ(__core__::apply_fn(mod->getline, args, 1),
            Value::Str("hello, world!"));
  EXPECT_EQ(__core__::apply_fn(mod->getline, args, 1),
            Value::Str("what is your name?"));
}
