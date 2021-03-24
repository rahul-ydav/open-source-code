#ifndef __EXERCISE_HPP__
#define __EXERCISE_HPP__

#include <mutex>
#include <queue>
#include <memory>
#include <thread>
#include <vector>


// Object that can be executed
struct Action {
    virtual void operator()() = 0;
};

// Queue that stores pointers to Actions
class ActionQueue {
    std::queue<std::unique_ptr<Action>> actions;
    std::mutex mutex;
public:
    void push(Action *action) {
        actions.push(std::unique_ptr<Action>(action));
    }
    std::unique_ptr<Action> pop() {
        std::unique_ptr<Action> action(std::move(actions.front()));
        actions.pop();
        return action;
    }
    bool empty() {
        return actions.empty();
    }
    void run_all();
    std::thread run_all_in_thread();
};

// Vector with attachd mutex
template<class T>
struct MVector {
    std::vector<T> data;
    std::mutex mutex;
};

// Object that runs a function on a given vector
template<class T>
class VectorAction : public Action {
protected:
    MVector<T> &mvector;
public:
    VectorAction(MVector<T> &mvector) : mvector(mvector) {}
};

#endif // __EXERCISE_HPP__
