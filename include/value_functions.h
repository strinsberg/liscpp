#ifndef LISCPP_VALUE_FUNCTIONS_H
#define LISCPP_VALUE_FUNCTIONS_H

#include "type.h"
#include "value.h"
#include <cstdint>

/* The primary purpose of these is because there are some limits on calling
 * overloaded constructors with literals when the underlying types are so
 * similar. E.g. Value(1) is ambiguous because we use int64_t and the compiler
 * does not know what type of int we want this to be. I don't want to write
 * Value(int64_t(1)) everywhere. So, I am investing in writing these functions
 * to make that easier in some places, both for library code implemented in C++
 * directly and for compiler code generation.
 *
 * Another useful thing can be to abstract away some calls to constructors and
 * new that would be required. E.g. I can avoid calling Value(ValType::String,
 * new GcString("string contents")) to make strings and just call
 * new_string("string contents"); It makes the construction of values explicit
 * where it helps.
 *
 * Unfortunately, not all of these functions save anything, and make it worse
 * where a call to Value(some_type_pointer) would be easier. But they are still
 * explicit where it may not always be obvious what type is being created. So,
 * some of them are a bit redundant, but it feels better to either use all
 * overloaded constructors or all explcit new functions. Some will be less
 * useful, but others will be helpful and reduce the code generation complexity
 * and make sure things are initialized properly where possible.
 *
 * Some types also have many constructors and it doesn't make sense to abstract
 * them all. Error constructor functions return an Error * because Error is a
 * single type like Value. So, there is no need for extras. We can just use
 * new_error(__error__::some_error_type(args, ...)).
 */

namespace liscpp {

namespace __value__ {
// Value Constructors //

// Primitives
Value new_nil();
Value new_bool(bool);
Value new_char(char);
Value new_int(int64_t);
Value new_float(double);

// String Types
Value new_symbol(const char *);
Value new_keyword(const char *);
Value new_string(const char *);
Value new_symbol(GcString *);
Value new_keyword(GcString *);
Value new_string(GcString *);

// Collections
Value new_list(List *);
Value new_vector(GcVector *);
Value new_map(GcMap *);
Value new_generator(Fn *, Fn *);

// Functions
Value new_fn(Fn *);
Value new_fn(const char *, Value (*)());
Value new_fn(const char *, Value (*)(Value));
Value new_fn(const char *, Value (*)(Value, Value));
Value new_fn(const char *, Value (*)(Value, Value, Value));
Value new_fn(const char *, Value (*)(Value, Value, Value, Value));
Value new_fn(const char *, Value (*)(Value, Value, Value, Value, Value));
Value new_fn(const char *, uint32_t, Value (*)(const Value[], uint32_t));
Value new_closure(const char *, GcVector *, uint32_t,
                  Value(GcVector *, const Value[], uint32_t));

// Stream
Value new_stream(std::istream *);
Value new_stream(std::ostream *);
Value new_stream(std::ifstream *);
Value new_stream(std::ofstream *);
Value new_stream(Stream *);

// Error
Value new_error(Error *);

} // namespace __value__

} // namespace liscpp

std::ostream &operator<<(std::ostream &os, const liscpp::Value &value);

#endif
