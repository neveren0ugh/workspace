#include <iostream>
#include <cmath>
#include<fstream>

using namespace std;

double func(double x) {
    return exp(sin(x));
}

double div_dif(double knot_array[], int point_number, double* values) {
    double div_val;
    double tmp;
    if (point_number == 0)
        return func(knot_array[0]);
    for (int m = point_number - 1; m > -1; m--) {
        div_val = 0;
        for (int i = 0; i < m + 1; i++) {
            tmp = 1;
            for (int j = 0; j < m + 1; j++) {
                if (i != j)
                    tmp *= (knot_array[i] - knot_array[j]);
            }
            div_val += (func(knot_array[i]) / tmp);
        }
        values[m] = div_val;
    }
    return div_val;
}

double polynom(double knot_array[], int point_number, double x, double* values) {
    double approx = 0;
    div_dif(knot_array, point_number, values);
     for (int i = point_number - 1; i > -1; i--) {
         approx += values[i];
         if (i != 0)
            approx *= (x - knot_array[i - 1]);
     }
     return approx;
}


int main() {
    ofstream stream("val3.txt");
    int x_left = 0, x_right = 10, point_number = 31;
    double h = 10. / (point_number - 1), knots[point_number], knots1[point_number], coefs[point_number];
    knots[0] = 0;
    for (int i = 1; i < point_number; i++) {
        knots[i] = knots[i - 1] + h;
    }
    const char csv_file_name[64] = "work3.csv";
    std::ofstream csv_file;
    csv_file.open(csv_file_name);
    for (size_t i = 0; i < point_number; ++i){
        csv_file << (2 * i + 1) * h / 2 << "," << polynom(knots, point_number, (2 * i + 1) * h / 2, knots1) << "\n";
    }
    csv_file.close();
    for ( int i = 0; i < point_number; i ++) {
        cout << (2 * i + 1) * h / 2 << "  " << polynom(knots, point_number, (2 * i + 1) * h / 2, knots1) << "\n";
    }

    return 0;
}