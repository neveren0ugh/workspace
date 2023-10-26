#include <iostream>

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
        return ((point.x < top_right.x) and (point.x > top_left.x) and (point.y < top_left.y) and (point.y > bottom_left.y));
    }
    void print() {
        cout << bottom_left.x << bottom_left.y << bottom_right.x << bottom_right.y << top_left.x << top_left.y << top_right.x << top_right.y << "\n";
    }
};


int main() {
    Coordinate nigga{1, 2}, balls{3, 4}, point1{1.5, 3};
    Rectangle puss{nigga, balls};
    return 0;
}
