# Liscpp Thoughts and Ideas

This is just a place for me to write some of my language design and implementation ideas down. I have a habit of writing my thoughts in commit messages or big comments. Better to put them in a separate place.

# General Language Design

I want to have the same syntax as Clojure, but I don't think that I am going to try to give the same semantics or have all the same language elements. Part of this is that the need for performant immutable data structures is not an easy problem to solve. I am sure I could look up implementations for these and get something working, but I don't want to tackle that until I have a lot of other necessary work done. Plus many languages work just fine with mutable data structures.

## Namespaces and Modules

I was going to build files into some sort of module that allowed them to run code on first require, or allow building scripts. I still want functionality like this, and even the possibility of building a module that can be passed around as a value. However, I think that building with namespaces as well will work really nicely.

The benefits of namespaces are:
* They are much simpler to implement. A `(ns some-name)` can just compile to the opening of a namespace and if another namespace is used the previous one will be closed and new one opened. If you write `(ns some-name ... code)` we can put all the code in the namespace and namespaces can be nested, could also have `ns` and `ns-nested` or something. The compiler can also eventually be made to organize nested directory structure as a namespace hierarchy, though this will not be something I go for right away. Finally, No singleton module classes need to be created. Just a namespace with all the value objects and probably a separate hidden namespace for all the hard-coded functions etc.
* They integrate really easily with C++ namespaces already. Really all we need here is to wrap code in a namespace. C++ does this already. It also makes things like allowing a namespace to be required without the qualifier possible because something like `(require [some.name.space :refer-all])` could just resolve to `using some::name::space;`.
* It will allow easily nesting namespaces and organizing code similar to Clojure. All Clojure core code can be accessed through a `clojure.core` namespace. I could wrap all library code inside an `lscpp` namespace and then nest other namespaces where appropriate. A user file or program could automatically be prepended with their project name as the first namespace and then each other namespace could be nested inside that for ensuring easy organization and preventing name clashes.

The downside to only using namespaces is that you cannot execute code at the top level. Everything will need to be inside functions. It could also present a problem if we were to allow mutating global variables. I suspect I will create a type similar to Atom in Clojure to do mutation and make all top level values `const`, though maybe this won't work if the `const` is for the object and not the variable itself.

This will be where modules will come in. A module can compile to a class and have non-const members and initialization. The created object can be a value if I want and use some indirection to access members, or they can not be full liscpp values, but allow for a more scriptlike coding style.

Using both eventually will allow for some flexibility. For now, I will probably tackle namespaces only. It is all I need for the internal libraries. It is also not really a huge deal to force wrapping all code execution in a function in a program. A compiled language that has to go through several steps to compile to a binary is not really going to be a scripting language anyway, until an interpreter can be implemented.

# Essential Forms

Given the data types I have introduced and the things a lisp-like language should do I am going to enumerate the essential forms or the language here. Some of these are more essential than others. For example, I do not need vector and map operations for the language to be useable, but they will be essential for it to be a useful language imo. I will implement them in an order that seems best to give as much to the language as possible and have working versions before spending the time to implement them all. I will also implement most of them in C++ or the compiler. Some will probably be implementable with the language, but it will always have less type checking overhead etc. to implement the internal bits directly in C++.

Note that a number of forms, mostly those that would be macros, will be generated through the compiler. For example, a let binding is just a block with a return value and local variable for the bindings. Lambdas will be converted to a function part and a value part by the compiler and inserted into the code and it's namespaces.

All of these forms and functions will be in the liscpp::core namespace.

## Special Forms
These will all be handled by the compiler and converted to C++ code that accomplishes the goal.
* `let` - scoped bindings and expressions to evaluate, returns the last expression
* `if` - conditional for a true and a false branch, no false branch returns nil (like `when` in Clojure)
* `cond` - an if else conditional with pairs of conditions and expressions
* `and` - short circuit and that will return the first falsey value or the final value if all are truthy
* `or` - short circuit or that will return the first truthy value or the final value if all values are falsey
* `loop` - loop recur from Clojure since I am not going to try and emulate tail recursion

## Collections
* `count` - return the length of the collection
* `nth` - return the nth element of the collection
* `first` - get the first value from a collection
* `<second|third|fourth|fifth>` - get the element of a collection
* `last` - get the last element from a collection
* `rest` - get the collection after the first value
* `drop-last` - like rest, but removes the last element
* `empty?` - is the collection empty

### Lists
* `list` - create a new list with the values passed as arguments
* `cons` - add a value onto a list
* `apply` - apply the first value as a function with the rest as arguments

### Vectors
* `vector` - create a new vector with the values passed as arguments
* `[]` - literal to create a vector, might be implemented more efficiently than `vector`
* `push!` - append a value onto the back of the vector
* `pop!` - pop the value from the back of the vector
* `set-nth!` - set the nth value to a new value

### Maps
* `map` - create a new map from pairs of values
* `{}` - literal for a map
* `assoc!` - 
* `dissoc!`
* `contains?` - check if a value is a key in a map
* `get` - get the value associated with the key from a map

### Iteration/Generators (collection generic)
All generators will need to have a function like `list` or `vector` on them. Generators can be called on generators to chain them efficiently instead of generating many intermediate collections. Some regular functions may consume the iterator and return a collection.
* `generator` - create a generator given two functions
* `filter` - generator that returns values that a predicate function returns truthy
* `map` - generator that maps a function over a collection
* `reduce` - generator that maps a function over a collection and accumulates a result
* `enumerate` - generator that returns [index value] pairs from a collection
* `range`- generator that returns a range of values
* `take` - generator that returns the first n values from a collection
* `drop` - generator that drops the first n values from a collection, for a list this will require traversing the first n elements, for a vector it should be able to jump to the nth element.

## All Values
* `=` - deep equality for values where possible
* `eq` - shallow equality based on primitive values or pointers
* `str` - returns a string with the display representation of each value argument concatenated together, no delimiters added
* `not` - returns the boolean opposite of the values truthiness

### Types
* `nil?`
* `bool?`
* `char?`
* `int?`
* `float?`
* `keyword?`
* `symbol?`
* `string?`
* `list?`
* `vector?`
* `map?`
* `generator?`
* `fn?`
* `stream?`
* `error?`

## Numeric

### Arithmetic
* `+` - sum a list of numbers
* `-` - subtract a list of numbers from the first value
* `*` - product of a list of numbers
* `/` - divide the first number by the rest
* `//` - same as divide, but integer division
* `%` - modulo of 2 numbers (need to be clear if this is C++ default behavior or modulo or remainder)

### Comparison
* `<` - check if all values are less than the next value (i.e. sorted smallest to largest)
* `<=` - check if all values are less or deep equal to the value before them (i.e. sorted non-decreasing)
* `>` - check if all values are greater than the next value (i.e. sorted largest to smallest)
* `>=` - check if all values are greater or deep equal to the next value (i.e. sorted non-increasing)

## I/O
Print functions insert a space delimiter.
* `prn` - print the external representation of a list of values to stdout
* `prnln` - print the external representation of a list of values to stdout with a linefeed
* `print` - print the display representation of a list of values to stdout
* `println` - print the display representation of a list of values to stdout with a linefeed

Write functions take a single argument to print and a stream argument.
* `wrt` - write the external representation of a value to a stream
* `wrtln` - write the external representation of a value to a stream with a linefeed
* `write` - write the display representation of a value to a stream
* `writeln` - write the display representation of a value to a stream with a linefeed

# Scratch

Namespaces for internal code are `liscpp` for all types. Functions and values are nested inside this namespace. `__name__` for internal functions and values and `name` for the public values used by the compiled code. This makes some implementation a little verbose, but helps to ensure that compiled code has no clashes without deliberate abuse.

I got types separated out. I moved value and type functions to separate files and namespaces. Just not sure if it is all ok yet. Everything needs to be modified to use these functions and the namespace style. Some value types like fn are still not quite in line with the changed I have made elsewhere.

The modio file needs to be redone as a namespace properly like core and the above idea.

The tests will all have to be rewritten.

I am still not sure how to work with things like GcString. Should it always be passed by pointer? Is it ok to have some function params and returns be references or regular objects? I feel like I always want to have the most specific and non-pointer type possible, but given the garbage collection pointers might be the correct option always in order to take advantage of that. I suppose I should have some constructor to make creating them easy, but none of these types should be passed around in a way that would end up copying unnecessarily. For example passing a GcString out of a function by const & is the right way normally to let others access something owned by an object, but here if it is passed out as a ref and used for new Values it will need to have another pointer to the string. Maybe we can just take the address of the reference, but why not just pass out the pointer and work with that.

I probably should take the very basic types and functions and comment out everything else for now. Build a simple test in a single file with a main and use what I have to see if the gc works the way I set things up. Also, just to get a feel for some of the changes and make some decisions about how to proceed. Organizing things and deciding what should be interfaced for the user and what should be interfaced for me is tough.

Made a generator. I think it could be simplified to a single type that accepts an initial value and two functions/closures. The functions would take the current value and next would return a new value and done would say if the value was right. The difficulty with this is that a custom function could not make the vector iterator very well without some complex closures, and I am not sure if I know what to do there yet. If I added a third function called value then it could work. The closure captures the vector and the updated item is the idx. I guess list gen does not work either as the stored value would have to be the list pointer, not the data value. Perhaps there could be two types or internal logic to make both possible with a single type. It is ok if I provide implementations for them, but kind of silly if I do not make it possible for a user to implement useful generators themselves. Could always store a collection of members and then implement the three functions to take them and next to return a new set of them. OR one could just expect the user to use closures for the functions, and we could provide no data members. You just provide two functions that work with captured variables. It still does not hurt to define the common ones in C++ to make them more efficient.

