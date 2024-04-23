# liscpp
Experiments with a lib for a lisp-like language that compiles to C++

**NOTE** the lib and any compiled liscpp code with use [The Boehm-Demers-Weiser conservative C/C++ Garbage Collector](https://github.com/ivmai/bdwgc). It is not fully setup yet, but if you read the code and miss this fact it might look like I am completely ignoring memory managment. However, when properly integrated calls to `new` will be intercepted and collections will use `gc_allocator` to allocate memory. This will give the resulting liscpp code gc without me having to try and write my own. 
