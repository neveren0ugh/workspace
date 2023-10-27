#pragma once
namespace coord {
    class coordinate {
    public:
        double x{0}, y{0};
        coordinate(double x_ax, double y_ax) : x(x_ax), y(y_ax) {}
    };
}