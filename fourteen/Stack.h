#pragma once
#include "PureStruct.h"

class Stack: public PureStruct{
public:
    std::vector <int> elements;

    virtual void push(int element);
    virtual int pop();
    virtual void print();
    virtual bool IsEmpty();
    virtual int len();
};