#pragma once
#include "PureStruct.h"

class DataStruct: public PureStruct{
protected:
    std::vector <int> elements;

public:

    virtual int pop();
    virtual void print();
};