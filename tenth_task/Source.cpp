#include <iostream>
#include "coordinate.h"
#include "rectangle.h"

using namespace std;
using namespace coord;
using namespace rect;

int main() {
    coordinate lb1(0, 0), rt1(6, 5), lb2(1, 1), rt2(2, 2);
    rectangle first(lb1, rt1), second(lb2, rt2);
    first.overlap(second);
    return 0;
}