#pragma once
#include <iostream>

class Ratio{
public:
    int num;
    int denom;

    Ratio(float number);
    Ratio(int a, int b);

    void print();
    void printRatio();

    Ratio operator+ (const Ratio& fr){
        return Ratio(num * fr.denom + fr.num * denom, denom * fr.denom);
    }
    Ratio operator- (const Ratio& fr){
        return Ratio(num * fr.denom - fr.num * denom, denom * fr.denom);
    }
    Ratio operator* (const Ratio& fr){
        return Ratio(num * fr.num, denom * fr.denom);
    }
};