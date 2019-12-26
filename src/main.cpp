#include <StaticSudoku/constexpr.hpp>

constexpr StaticSudoku::Details::ArrayType unsolved{
        0, 0, 0, 0, 2, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 5, 0, 0, 9,
        0, 0, 0, 0, 8, 6, 0, 0, 0,
        0, 5, 0, 6, 0, 0, 0, 0, 2,
        0, 6, 0, 0, 9, 0, 8, 4, 0,
        7, 0, 0, 0, 0, 0, 0, 5, 0,
        0, 0, 7, 0, 5, 0, 0, 9, 0,
        5, 9, 0, 4, 0, 1, 0, 2, 0,
        0, 2, 1, 7, 0, 0, 0, 0, 6
};

constexpr StaticSudoku::Details::ArrayType solved = StaticSudoku::constexprSolve(unsolved);

int main() {
    return 0;
}
