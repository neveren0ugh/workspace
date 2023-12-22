#include "Ratio.h"

int main(){
    Ratio test1(-5, -3);
    test1.print();
    Ratio test2(10, 6);
    test2.printRatio();
    (test2+test1).print();
    (test2-test1).printRatio();
    (test1*test2).print();

    Ratio test3(0, 0);
    test3.print();
    return 0;
}