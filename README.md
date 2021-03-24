[C++ Exercise]

Step 1

A "MVector" is structure containing both a "std::vector" and a "std::mutex"
An "Action" is an abstract class that runs a virtual function upon calling its "()" operator
A "VectorAction" is defined as a class able to execute a simple task on a "MVector"

Your first objective is to inherit the "VectorAction" interface to implement the following behaviors:
  - Sorting (in the "SortVector" class)
  - Printing (in the "PrintVector" class)
  - Insertion (in the "AppendToVector" class)
You can refer to the "void test1()" function to see how these classes are meant to be instanciated
Make sure any operation on a vector is thread-safe

Step 2

An "ActionQueue" is a class that holds a queue of "Action"

Your objective is to implement two methods:
  - "ActionQueue::run_all" that pops "Actions" from the stack and run them
  - "ActionQueue::run_all_in_thread" that does the same but in a separate thread

You can refer to the "void test2()" function to see how and when these functions are called

T.B.N

This exercie is designed to evaluate your comprehension and knowledge of C++
As such, your functions are not meant to be more than 1~5 line each
You can refer to C++ documentation if need be
