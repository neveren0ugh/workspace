#pragma once
#include "PureStruct.h"
#include "Node.h"

class LinkedList : public PureStruct{
public:
    Node* head;
    Node* tail;

    LinkedList();
    virtual void push(int element);
    virtual int pop();
    virtual void print();
    virtual bool IsEmpty();
    virtual int len();
};