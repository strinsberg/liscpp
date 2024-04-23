#include "type.h"
#include <gtest/gtest.h>
#include <sstream>

// For now these are not complete as I expect the representation might change

TEST(ValueTypeStr, does_it_convert_to_a_string) {
  EXPECT_EQ(type::str(ValueType::List), "ValueType::List");
}

TEST(ValueTypeOperatorOstream, does_it_send_the_string_to_the_stream) {
  std::ostringstream oss("");
  oss << ValueType::Nil;
  EXPECT_EQ(oss.str(), "ValueType::Nil");
}

TEST(FnTypeStr, does_it_convert_to_a_string) {
  EXPECT_EQ(type::str(FnType::FnAny), "FnType::FnAny");
}

TEST(FnTypeOperatorOstream, does_it_send_the_string_to_the_stream) {
  std::ostringstream oss("");
  oss << FnType::Fn0;
  EXPECT_EQ(oss.str(), "FnType::Fn0");
}

TEST(StreamTypeStr, does_it_convert_to_a_string) {
  EXPECT_EQ(type::str(StreamType::Input), "StreamType::Input");
}

TEST(StreamTypeOperatorOstream, does_it_send_the_string_to_the_stream) {
  std::ostringstream oss("");
  oss << StreamType::Output;
  EXPECT_EQ(oss.str(), "StreamType::Output");
}
