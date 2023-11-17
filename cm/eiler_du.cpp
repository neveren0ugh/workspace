#include <iostream>
#include <cmath>

using namespace std;

float func(float x);

float th_func(float x);

void print_grid(float* to_be_printed, float* to_be_printed1, float* to_be_printed2, int amount, float knots[]);

void solver_ad(float* knots, float* solution_grid, float* solution_grid_der, int amount, float step);

void solver_runge(float* knots, float* solution_grid, float* solution_grid_der, int amount, float step);

void solver(float* solution_grid_der, float* solution_grid, float knots[], float step, float amount);

int main() {
    int amount = 51;
    float step = 0.05, knots[amount+1], solution_grid[amount+1], solution_grid_der[amount+1], sg1[amount+1], sgd1[amount+1], sg2[amount+1], sgd2[amount+1];
    for (int i = 0; i < amount + 1; i++) {
        knots[i] = step * i;
    }

    solution_grid[0] = 1.;
    solution_grid_der[0] = 1.;
    sg1[0] = 1.;
    sgd1[0] = 1.;
    sg2[0] = 1.;
    sgd2[0] = 1.;
    sg2[1] = 1.04871;
    sgd2[1] = 0.947527;
    sg2[2] = 1.09467;
    sgd2[2] = 0.890266;

    solver(solution_grid_der,solution_grid, knots, step, amount);
    solver_runge(knots, sg1, sgd1, amount, step);
    solver_ad(knots, sg2, sgd2, amount, step);
    print_grid(solution_grid, sg1, sg2, amount, knots);

    return 0;
}

float func(float x, float y0, float y1) {
    return 2*x*tan(x)* atan(x) / (x*x + 1) - 2*x*y1 / (x*x + 1) - 2*x*tan(x)*y0 / (x*x + 1) - cos(x);
}

float th_func(float x) {
    return cos(x) + atan(x);
}

void solver(float* solution_grid_der, float* solution_grid, float knots[], float step, float amount) {
    for (int i = 1; i < amount + 1; i++) {
        solution_grid_der[i] = solution_grid_der[i-1] + step * func(knots[i-1], solution_grid[i-1], solution_grid_der[i-1]);
        solution_grid[i] = solution_grid[i-1] + step * solution_grid_der[i-1];
    }
}

void solver_runge(float* knots, float* solution_grid, float* solution_grid_der, int amount, float step) {
    float q0, q1, q2, q3;
    float k0, k1, k2, k3;
    for (int i = 1; i < amount; i++) {
        q0 = func(knots[i-1], solution_grid[i-1], solution_grid_der[i-1]);
        k0 = solution_grid_der[i-1];
        q1 = func(knots[i-1] + step / 2., solution_grid[i-1] + k0 * step / 2., solution_grid_der[i-1] + q0 * step / 2.);
        k1 = solution_grid_der[i-1] + q0 * step / 2.;
        q2 = func(knots[i-1] + step / 2., solution_grid[i-1] + k1 * step / 2., solution_grid_der[i-1] + q1 * step / 2.);
        k2 = solution_grid_der[i-1] + q1 * step / 2.;
        q3 = func(knots[i-1] + step, solution_grid[i-1] + k2 * step, solution_grid_der[i-1] + q2 * step);
        k3 = solution_grid_der[i-1] + q2 * step;

        solution_grid_der[i] = solution_grid_der[i-1] + step / 6. * (q0 + 2 * q1 + 2 * q2 + q3);
        solution_grid[i] = solution_grid[i-1] + step / 6. * (k0 + 2 * k1 + 2 * k2 + k3);
    }
}

void solver_ad(float* knots, float* solution_grid, float* solution_grid_der, int amount, float step) {
    float k1, k2, k3;
    for (int i = 3; i < amount; i++) {
        k1 = func(knots[i-1], solution_grid[i-1], solution_grid_der[i-1]);
        k2 = func(knots[i-2], solution_grid[i-2], solution_grid_der[i-2]);
        k3 = func(knots[i-3], solution_grid[i-3], solution_grid_der[i-3]);

        solution_grid_der[i] = solution_grid_der[i-1] + (23. * k1 - 16. * k2 + 5. * k3) * step / 12.;
        solution_grid[i] = solution_grid[i-1] + (23. * solution_grid_der[i-1] - 16. * solution_grid_der[i-2] + 5. * solution_grid_der[i-3]) * step / 12.;
    }
}

void print_grid(float* to_be_printed, float* to_be_printed1, float* to_be_printed2, int amount, float knots[]) {
    for (int i = 0; i < amount; i++) {
        cout << to_be_printed[i] << "\t" << th_func(knots[i]) << "\t" << to_be_printed1[i] << "\t" << to_be_printed2[i] << "\n";
    }
}
