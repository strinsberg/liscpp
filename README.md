# liscpp
Experiments with a lib for a lisp-like language that compiles to C++. This is essentially a replacement for [Rusp](https://github.com/strinsberg/rusp), which I felt had some issues and was unsatisfied with the realities of using shared pointers for dynamic memory.

Currently, this is just the start of a lib for compiled programs to import. It has some tests for things with a more solidified structure. It also will have tests that can approximate code generated by the compiler to get the C++ correct. I will also eventually put together some simple benchmark type tests to allow checking some different possibilities for compiled code and library implementations.

**NOTE** the lib and any compiled liscpp code with use [The Boehm-Demers-Weiser conservative C/C++ Garbage Collector](https://github.com/ivmai/bdwgc). It is not fully setup yet, but if you read the code and miss this fact it might look like I am completely ignoring memory managment. However, when properly integrated calls to `new` will be intercepted and collections will use `gc_allocator` to allocate memory. This will give the resulting liscpp code gc without me having to try and write my own. 
