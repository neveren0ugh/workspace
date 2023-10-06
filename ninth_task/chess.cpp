#include <iostream>
#include <array>
#include <random>

using namespace std;

bool k_is_capable(int king_pos[2], int king_b_pos[2]) {
    if ((king_b_pos[0] - king_pos[0] <= 1) and (king_b_pos[1] - king_pos[1] <= 1))
        return false;
    else
        return true;
}

bool rook_b_close(int king_b_pos[2], int rook_pos[2]) {
    return !((king_b_pos[0] - rook_pos[0] <= 1) or (king_b_pos[1] - rook_pos[1] <= 1));
}

bool pos_optimization_start(int king_pos[2], int king_b_pos[2], int rook_pos[2]) {
    bool is_optimized = false;
    while (!is_optimized) {
        if ((rook_b_close(king_b_pos, rook_pos)) and (rook_pos[1] != 1) and (king_b_pos[1] > 2)) {
            if () !!
        }
    }
}

int main() {
    int king_b_pos[2], king_pos[2], rook_pos[2];
    char filler;
    array<array<char,8>,8> field;
    filler = '_';
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            field[i][j] = filler;
    }
    return 0;
}
