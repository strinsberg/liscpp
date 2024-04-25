# Liscpp Thoughts and Ideas

This is just a place for me to write some of my language design and implementation ideas down. I have a habit of writing my thoughts in commit messages or big comments. Better to put them in a separate place.

## General Language Design

I want to have the same syntax as Clojure, but I don't think that I am going to try to give the same semantics or have all the same language elements. Part of this is that the need for performant immutable data structures is not an easy problem to solve. I am sure I could look up implementations for these and get something working, but I don't want to tackle that until I have a lot of other necessary work done. Plus many languages work just fine with mutable data structures.

### Namespaces and Modules

I was going to build files into some sort of module that allowed them to run code on first require, or allow building scripts. I still want functionality like this, and even the possibility of building a module that can be passed around as a value. However, I think that building with namespaces as well will work really nicely.

The benefits of namespaces are:
* They are much simpler to implement. A `(ns some-name)` can just compile to the opening of a namespace and if another namespace is used the previous one will be closed and new one opened. If you write `(ns some-name ... code)` we can put all the code in the namespace and namespaces can be nested, could also have `ns` and `ns-nested` or something. The compiler can also eventually be made to organize nested directory structure as a namespace hierarchy, though this will not be something I go for right away. Finally, No singleton module classes need to be created. Just a namespace with all the value objects and probably a separate hidden namespace for all the hard-coded functions etc.
* They integrate really easily with C++ namespaces already. Really all we need here is to wrap code in a namespace. C++ does this already. It also makes things like allowing a namespace to be required without the qualifier possible because something like `(require [some.name.space :refer-all])` could just resolve to `using some::name::space;`.
* It will allow easily nesting namespaces and organizing code similar to Clojure. All Clojure core code can be accessed through a `clojure.core` namespace. I could wrap all library code inside an `lscpp` namespace and then nest other namespaces where appropriate. A user file or program could automatically be prepended with their project name as the first namespace and then each other namespace could be nested inside that for ensuring easy organization and preventing name clashes.

The downside to only using namespaces is that you cannot execute code at the top level. Everything will need to be inside functions. It could also present a problem if we were to allow mutating global variables. I suspect I will create a type similar to Atom in Clojure to do mutation and make all top level values `const`, though maybe this won't work if the `const` is for the object and not the variable itself.

This will be where modules will come in. A module can compile to a class and have non-const members and initialization. The created object can be a value if I want and use some indirection to access members, or they can not be full liscpp values, but allow for a more scriptlike coding style.

Using both eventually will allow for some flexibility. For now, I will probably tackle namespaces only. It is all I need for the internal libraries. It is also not really a huge deal to force wrapping all code execution in a function in a program. A compiled language that has to go through several steps to compile to a binary is not really going to be a scripting language anyway, until an interpreter can be implemented.
