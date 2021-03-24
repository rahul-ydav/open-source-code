//To run, use the command line :-    g++ -pthread exercise.cpp

#include "exercise.hpp"

#include <iostream>
#include <functional>
#include <sstream>
#include<algorithm>


// Write your own code below

template<class T>
class SortVector: public VectorAction<T> {
    public:
        SortVector(MVector<T> &mvector) : VectorAction<T>(mvector)
        {
            std::sort(mvector.data.begin(), mvector.data.end());
        }

        void operator()() {}

};

template<class T>
class PrintVector: public VectorAction<T> {
    public:
        PrintVector(MVector<T> &mvector) : VectorAction<T>(mvector)
        {
            for(auto &i : mvector.data)
            {
                std::cout<<i<<", ";
            }
            std::cout<<"\n";
        }
        void operator()() {}

};


template<class T>
class AppendToVector: public VectorAction<T> {
    public:
        AppendToVector(MVector<T> &mvector, T val) : VectorAction<T>(mvector)
        {
            mvector.data.push_back(val);
        }
        void operator()() {}
};

void ActionQueue::run_all() {
    actions.pop();
}
void foo(ActionQueue* actions) {actions->pop();}
std::thread ActionQueue::run_all_in_thread()
{
    std::thread t(foo, this);
    return t;
}


// Nothing to edit below this point

void test1() {

    std::cout
        << std::endl
        << "[TEST1]" << std::endl
        << "- Main thread: Append / Sort / Print" << std::endl
        << std::endl
        << "Expected output:" << std::endl
        << "1 100 1000 10" << std::endl
        << "0.0001 0.001 0.01 0.1 " << std::endl
        << std::endl
        << "Output:" << std::endl;

    // Declare two vectors
    MVector<int> integers;
    MVector<float> floats;

    // Initialize the vectors
    integers.data = { 1, 1000, 100 };
    floats.data = { 0.01, 0.1, 0.0001 };

    // Bind Actions
    ActionQueue actions;
    actions.push(new SortVector<int>(integers));
    actions.push(new AppendToVector<float>(floats, 0.001));
    actions.push(new AppendToVector<int>(integers, 10));
    actions.push(new SortVector<float>(floats));
    actions.push(new PrintVector<int>(integers));
    actions.push(new PrintVector<float>(floats));

  

    // Run Actions
    actions.run_all();
}

void test2() {

    std::cout
        << std::endl
        << "[TEST2]" << std::endl
        << "- Sub threads: Append" << std::endl
        << "- Main thread: Sort / Print" << std::endl
        << std::endl
        << "Expected output:" << std::endl
        << "First T1W0 T1W1 T1W2 T1W3 T1W4 T2W0 T2W1 T2W2 T2W3 T2W4 T3W0 T3W1 T3W2 T3W3 T3W4" << std::endl
        << std::endl
        << "Output:" << std::endl;

    // Generate words
    const int word_per_thread = 5;  
    MVector<std::string> words = {{ "First" }};
    std::function<Action *(int, int)> append_name = [&](int thread, int word) {
        std::stringstream ss;
        ss << "T" << thread << "W" << word;
        return new AppendToVector<std::string>(words, ss.str());
    };

    // Bind multiple Actions per thread
    ActionQueue actions1;
    ActionQueue actions2;
    ActionQueue actions3;
    for (int i = 0; i < word_per_thread; ++i) {
        actions1.push(append_name(1, i));
        actions2.push(append_name(2, i));
        actions3.push(append_name(3, i));
    }

    // Run Actions
    std::thread t1(std::move(actions1.run_all_in_thread()));
    std::thread t2(std::move(actions2.run_all_in_thread()));
    std::thread t3(std::move(actions3.run_all_in_thread()));
    t1.join();
    t2.join();
    t3.join();

    // Checks the output
    SortVector<std::string> sort(words);
    PrintVector<std::string> print(words);
    sort();
    print();
}

int main() {
    test1();
    test2();
}