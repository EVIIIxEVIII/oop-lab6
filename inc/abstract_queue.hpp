#pragma once

template <typename T>
class IQueue {
public:
    virtual ~IQueue() = default;
    virtual void push(const T& value) = 0;
    virtual bool pop(T& out) = 0;
    virtual bool empty() const = 0;
};
