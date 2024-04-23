#ifndef LISCPP_MOD_IO_H
#define LISCPP_MOD_IO_H

#include "value.h"
#include <cstdint>
#include <vector>

/* For now this serves 2 purposes.
 * 1. To experiement with what is a good way to design a module, both for the
 *    core liscpp library, but also for what they could look like in compiled
 *    code gneration.
 * 2. To wrap some of the io operations in a module rather than having them
 *    float around in the global namespace, which I would like to keep for
 *    language fundamentals and things that are ubiquitous.
 *
 * It will not be enforced by an interface because every module will be it's
 * own unique type, but each module MUST have these properties.
 * 1. All constructors must be private.
 * 2. Has a static method that returns a pointer to the module and is
 *    responsible for makign sure the first time it is called it initializes
 *    the singleton module object.
 * 3. Has public Value fields for every value and function defined in the
 *    module.
 * 4. Has a following namespace with definitions for all actual c++ functions
 *    containing the logic for public functions in the module.
 * 5. Since anonymous lambdas will have their function bodies declared
 *    separately, they should not be accessible to outside code but I am not
 *    sure where I will put them. NOTE this only applies to compiled modules.
 */

class ModIo {
public:
  ~ModIo() {}
  static ModIo *require();

  // Public fields holding module values and functions
  Value getline;

private:
  void init();
  static ModIo *m_mod;

  // All Value members are initialized to nil automatically
  ModIo() {}

  // Deleted constructors
  ModIo(const ModIo &) = delete;
  ModIo(ModIo &&) = delete;
  ModIo &operator=(const ModIo &) = delete;
  ModIo &operator=(ModIo &&) = delete;
};

// These are the functions present in the module
namespace __mod_io__ {
Value getline(Value);
} // namespace __mod_io__

#endif
