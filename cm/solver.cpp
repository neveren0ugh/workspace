#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double func(double x);

void dichotomy_method(double left_border, double right_border, double precision);

void newton_method(double left_border, double right_border, double precision);

void chord_method(double left_border, double right_border, double precision);

int main() {
    double any = 0, any1 = 2.5, prec = 1e-3;
    dichotomy_method(any, any1, prec);
    chord_method(any, any1, prec);
    return 0;
}

double func(double x) {
    return sin(exp(x));
}

void dichotomy_method(double left_border, double right_border, double precision) {
    if (!precision)
        exit(-1);
    vector <double> solutions, sections{left_border};
    double tmp = left_border;
    while (tmp <= right_border) {
        if (func(sections.back())*func(tmp) < 0) {
            sections.push_back(tmp);
        }
        tmp += precision;
    }
    double a, b, x0;
    for (int i = 0; i < sections.size() - 1; i++) {
        a = sections[i];
        b = sections[i+1];
        x0 = (a + b) / 2.;
        while (!((func(x0) < precision) && (abs(b - x0) < precision))) {
            if (func(b)*func(x0) < 0)
                a = x0;
            else
                b = x0;
            x0 = (a + b) / 2.;
        }
        cout << x0 << "\n";
    }
}


void chord_method(double left_border, double right_border, double precision) {
    if (!precision)
        exit(-1);
    vector <double> solutions, sections{left_border};
    double tmp = left_border;
    while (tmp <= right_border) {
        if (func(sections.back())*func(tmp) < 0) {
            sections.push_back(tmp);
        }
        tmp += precision;
    }
    double x1, x2, x3;
    for (int i = 0; i < sections.size() - 1; i++) {
        x1 = sections[i];
        x2 = sections[i+1];
        while (!((func(x2) < precision) && (abs(x2 - x1) < precision))) {
            x1 = x1 - (x2 - x1) * func(x1) / (func(x2) - func(x1));
            x2 = x2 - (x1 - x2) * func(x2) / (func(x1) - func(x2));
        }
        cout << x2 << "\n";
    }
}