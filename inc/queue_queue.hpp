#pragma once

#include <queue>
#include "abstract_queue.hpp"

template<typename T>
class Queue : public IQueue<T> {
public:
    void push(const T& value) override { queue_.push(value); }
    bool pop(T& out) override {
        if (queue_.empty()) {
            return false;
        }

        out = queue_.front();
        queue_.pop();
        return true;
    }
    bool empty() const override { return queue_.empty(); }

private:
    std::queue<T> queue_;
};
