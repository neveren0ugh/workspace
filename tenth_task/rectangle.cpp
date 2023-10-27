#include "rectangle.h"
#include <cmath>
#include "coordinate.h"

using namespace std;
using namespace coord;
using namespace rect;

rectangle::rectangle(coordinate bot_left, coordinate t_right) : bottom_left(bot_left), top_right(t_right), bottom_right(t_right.x, bot_left.y), top_left(bot_left.x, t_right.y) {}
    bool rectangle::in_rectangle(coordinate point) {
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
    coordinate rectangle::get_left_bottom() {
        return rectangle::bottom_left;
    }
    coordinate rectangle::get_right_bottom() {
        return rectangle::bottom_right;
    }
    coordinate rectangle::get_left_top() {
        return rectangle::top_left;
    }
    coordinate rectangle::get_right_top() {
        return rectangle::top_right;
    }
    void rectangle::overlap(rectangle second) {
        if (in_rectangle(second.get_left_bottom())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        if (in_rectangle(second.get_left_top())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        if (in_rectangle(second.get_right_bottom())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        if (in_rectangle(second.get_right_top())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        if (second.in_rectangle(get_left_bottom())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        if (second.in_rectangle(get_left_top())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        if (second.in_rectangle(get_right_bottom())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        if (second.in_rectangle(get_right_top())) {
            cout << "rectangles do overlap";
            exit(0);
        }
        cout << "rectangles do not overlap";
    }