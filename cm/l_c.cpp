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
    for (int i = 0; i < point_number; i++) {
        tmp = 1;
        for (int j = 0; j < point_number; j++) {
            if (i != j)
                tmp *= (x - knot_array[j]) / (knot_array[i] - knot_array[j]);;
        }
        poly_val += func(knot_array[i]) * tmp;
    }
    return poly_val;
}

int main() {
    int x_left = 0, x_right = 10, point_number = 31;
    float h = 10. / (point_number - 1), knots[point_number]; //c = coef, l = basis
    knots[0] = x_left;
    for (int i = 1; i < point_number; i++) {
        knots[i] = x_left + i * h;
    }
    const char csv_file_name[64] = "work1.csv";
    std::ofstream csv_file;
    csv_file.open(csv_file_name);
    for (size_t i = 0; i < point_number; ++i){
        csv_file << (2 * i + 1) * h / 2 << "," << polynom(knots, (2 * i + 1) * h / 2, point_number) << "\n";
    }
    csv_file.close();
    for ( int i = 0; i < point_number; i ++) {
        cout << (2 * i + 1) * h / 2 << "  " << polynom(knots, (2 * i + 1) * h / 2, point_number) << "\n";
    }
    return 0;
}
