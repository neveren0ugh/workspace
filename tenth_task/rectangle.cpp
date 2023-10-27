#include <iostream>
#include <cmath>

using namespace std;

class Coordinate {
public:
    double x, y;
    Coordinate() {x = 0, y = 0;};
    Coordinate(double x_ax, double y_ax) {
        x = x_ax;
        y = y_ax;
    }
    double get_x() {
        return x;
    }
    double get_y() {
        return y;
    }
};

class Rectangle {
private:
    Coordinate bottom_left{};
    Coordinate bottom_right{};
    Coordinate top_left{};
    Coordinate top_right{};
public:
    Rectangle() {0;};
    Rectangle(Coordinate bot_left, Coordinate t_right) {
        bottom_left = bot_left;
        top_right = t_right;
        bottom_right.y = bot_left.y;
        bottom_right.x = t_right.x;
        top_left.x = bot_left.x;
        top_left.y = t_right.y;
    }
    bool in_rectangle(Coordinate point) {
        if ((abs(point.x - top_right.x) < 1e-6) and (abs(point.y - top_right.y) < 1e-6))
            return true;
        if ((abs(point.x - top_left.x) < 1e-6) and (abs(point.y - top_left.y) < 1e-6))
            return true;
        if ((abs(point.x - bottom_left.x) < 1e-6) and (abs(point.y - bottom_left.y) < 1e-6))
            return true;
        if ((abs(point.x - bottom_right.x) < 1e-6) and (abs(point.y - bottom_right.y) < 1e-6))
            return true;
        return ((point.x < top_right.x) and (point.x > top_left.x) and (point.y < top_left.y) and (point.y > bottom_left.y));
    }
    void print() {
        cout << bottom_left.x << bottom_left.y << bottom_right.x << bottom_right.y << top_left.x << top_left.y << top_right.x << top_right.y << "\n";
    }
    Coordinate get_left_bottom() {
        return bottom_left;
    }
    Coordinate get_right_bottom() {
        return bottom_right;
    }
    Coordinate get_left_top() {
        return top_left;
    }
    Coordinate get_right_top() {
        return top_right;
    }
};


int main() {
    Coordinate check(1, 1), lb1(0, 0), rt1(6, 5), lb2(-1, -1), rt2(10, 10);
    Rectangle first(lb1, rt1), second(lb2, rt2);
    if (first.in_rectangle(second.get_left_bottom()))
        cout << "Rectangles do overlap";
    if (first.in_rectangle(second.get_left_top()))
        cout << "Rectangles do overlap";
    if (first.in_rectangle(second.get_right_bottom()))
        cout << "Rectangles do overlap";
    if (first.in_rectangle(second.get_right_top()))
        cout << "Rectangles do overlap";
    return 0;
}
