#include "Stack.h"
#include "Queue.h"

int main(){
    Stack test1;
    Queue test2;

    test1.push(1);
    test1.push(2);
    test1.push(3);
    test1.print();
    test1.pop();
    test1.print();

}