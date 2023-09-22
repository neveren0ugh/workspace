#include <iostream>
#include <cmath>
#include<fstream>

using namespace std;

float func(float x) {
    return exp(sin(x));
}

float polynom(float knot_array[], float x, int point_number) {
    float poly_val = 0;
    float tmp;
    for (int i = 1; i < point_number; i++) {
        tmp = 1;
        for (int j = 1; j < point_number; j++) {
            if (i != j)
                tmp *= (x - knot_array[j]) / (knot_array[i] - knot_array[j]);;
        }
        poly_val += func(knot_array[i]) * tmp;
    }
    return poly_val;
}

int main() {
    ofstream stream("val2.txt");
    int x_left = 0, x_right = 10, point_number = 31;
    float knots[point_number], tmp; //c = coef, l = basis
    for (int i = 0; i < point_number; i++) {
        knots[i] = (x_right + x_left) / 2. + (x_right - x_left) * cos((2 * i + 1) * M_PI / (2 * point_number)) / 2;
    }
    const char csv_file_name[64] = "work2.csv";
    std::ofstream csv_file;
    csv_file.open(csv_file_name);
    for (size_t i = 0; i < point_number; ++i){
        csv_file << (knots[i] + knots[i + 1]) / 2 << "," << polynom(knots, (knots[i] + knots[i + 1]) / 2, point_number) << "\n";
    }
    csv_file.close();
    for ( int i = 0; i < point_number - 1; i ++) {
        tmp = polynom(knots, (knots[i] + knots[i + 1]) / 2, point_number);
        cout << (knots[i] + knots[i + 1]) / 2 << "  " << tmp << "\n";
    }
    return 0;
}