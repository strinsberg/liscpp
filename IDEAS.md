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

# Scratch

Namespaces for internal code are `liscpp` for all types. Functions and values are nested inside this namespace. `__name__` for internal functions and values and `name` for the public values used by the compiled code. This makes some implementation a little verbose, but helps to ensure that compiled code has no clashes without deliberate abuse.

I got types separated out. I moved value and type functions to separate files and namespaces. Just not sure if it is all ok yet. Everything needs to be modified to use these functions and the namespace style. Some value types like fn are still not quite in line with the changed I have made elsewhere.

The modio file needs to be redone as a namespace properly like core and the above idea.

The tests will all have to be rewritten.

I am still not sure how to work with things like GcString. Should it always be passed by pointer? Is it ok to have some function params and returns be references or regular objects? I feel like I always want to have the most specific and non-pointer type possible, but given the garbage collection pointers might be the correct option always in order to take advantage of that. I suppose I should have some constructor to make creating them easy, but none of these types should be passed around in a way that would end up copying unnecessarily. For example passing a GcString out of a function by const & is the right way normally to let others access something owned by an object, but here if it is passed out as a ref and used for new Values it will need to have another pointer to the string. Maybe we can just take the address of the reference, but why not just pass out the pointer and work with that.

I probably should take the very basic types and functions and comment out everything else for now. Build a simple test in a single file with a main and use what I have to see if the gc works the way I set things up. Also, just to get a feel for some of the changes and make some decisions about how to proceed. Organizing things and deciding what should be interfaced for the user and what should be interfaced for me is tough.

Made a generator. I think it could be simplified to a single type that accepts an initial value and two functions/closures. The functions would take the current value and next would return a new value and done would say if the value was right. The difficulty with this is that a custom function could not make the vector iterator very well without some complex closures, and I am not sure if I know what to do there yet. If I added a third function called value then it could work. The closure captures the vector and the updated item is the idx. I guess list gen does not work either as the stored value would have to be the list pointer, not the data value. Perhaps there could be two types or internal logic to make both possible with a single type. It is ok if I provide implementations for them, but kind of silly if I do not make it possible for a user to implement useful generators themselves. Could always store a collection of members and then implement the three functions to take them and next to return a new set of them. OR one could just expect the user to use closures for the functions, and we could provide no data members. You just provide two functions that work with captured variables. It still does not hurt to define the common ones in C++ to make them more efficient.

