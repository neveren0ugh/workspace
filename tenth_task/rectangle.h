#pragma once
#include <iostream>
#include <cmath>
#include "coordinate.h"

using namespace std;
using namespace coord;

namespace rect {
    class rectangle {
    private:
        coordinate bottom_left{0, 0};
        coordinate bottom_right{ 0, 0 };
        coordinate top_left{ 0, 0 };
        coordinate top_right{0, 0};
    public:
        rectangle(coordinate bot_left, coordinate t_right);
        bool in_rectangle(coordinate point);
        coordinate get_left_bottom();
        coordinate get_right_bottom();
        coordinate get_left_top();
        coordinate get_right_top();
        void overlap(rectangle second);
    };
}

