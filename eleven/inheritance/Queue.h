#pragma once
#include "PureStruct.h"

class Queue: public PureStruct {
private:
    std::vector <int> elements;

public:

    virtual void push(int element);
    virtual int pop();
    virtual void print();
};