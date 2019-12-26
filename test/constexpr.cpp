#include "catch.hpp"
#include <StaticSudoku/constexpr.hpp>

namespace StaticSudoku::Test {

constexpr Details::ArrayType unsolved0{
    0, 0, 6, 0, 0, 2, 0, 0, 0,
    0, 1, 5, 0, 8, 0, 6, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 8, 0,
    6, 0, 0, 0, 0, 5, 0, 0, 0,
    0, 0, 4, 0, 0, 0, 0, 0, 8,
    0, 5, 0, 6, 4, 0, 1, 0, 0,
    2, 0, 0, 4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 6, 3, 0, 0,
    0, 4, 9, 2, 0, 8, 0, 0, 0
};
constexpr Details::ArrayType solved0{
    3, 8, 6, 5, 9, 2, 4, 7, 1,
    9, 1, 5, 7, 8, 4, 6, 2, 3,
    4, 2, 7, 1, 6, 3, 9, 8, 5,
    6, 3, 1, 8, 7, 5, 2, 9, 4,
    7, 9, 4, 3, 2, 1, 5, 6, 8,
    8, 5, 2, 6, 4, 9, 1, 3, 7,
    2, 6, 3, 4, 1, 7, 8, 5, 9,
    1, 7, 8, 9, 5, 6, 3, 4, 2,
    5, 4, 9, 2, 3, 8, 7, 1, 6
};

constexpr Details::ArrayType unsolved1{
    0, 0, 0, 0, 0, 0, 0, 7, 0,
    0, 0, 0, 0, 0, 9, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 3, 6,
    1, 0, 0, 0, 3, 4, 0, 0, 0,
    3, 7, 2, 0, 0, 1, 0, 6, 0,
    0, 0, 6, 0, 2, 0, 0, 0, 0,
    0, 8, 1, 7, 0, 0, 0, 0, 4,
    0, 6, 3, 1, 0, 0, 0, 9, 2,
    7, 0, 0, 0, 9, 0, 0, 0, 0
};
constexpr Details::ArrayType solved1{
    8, 4, 9, 3, 1, 6, 2, 7, 5,
    6, 3, 5, 2, 7, 9, 8, 4, 1,
    2, 1, 7, 4, 8, 5, 9, 3, 6,
    1, 9, 8, 6, 3, 4, 5, 2, 7,
    3, 7, 2, 8, 5, 1, 4, 6, 9,
    4, 5, 6, 9, 2, 7, 1, 8, 3,
    9, 8, 1, 7, 6, 2, 3, 5, 4,
    5, 6, 3, 1, 4, 8, 7, 9, 2,
    7, 2, 4, 5, 9, 3, 6, 1, 8
};

constexpr Details::ArrayType unsolved2{
    0, 0, 2, 9, 0, 0, 0, 4, 3,
    3, 0, 6, 0, 0, 0, 0, 0, 2,
    0, 5, 0, 6, 0, 2, 9, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 9, 0, 6, 4,
    0, 0, 7, 0, 0, 4, 5, 0, 0,
    1, 0, 0, 0, 0, 0, 7, 0, 0,
    6, 0, 0, 7, 0, 5, 0, 1, 9,
    9, 0, 0, 0, 0, 6, 0, 0, 0
};
constexpr Details::ArrayType solved2{
    7, 8, 2, 9, 5, 1, 6, 4, 3,
    3, 9, 6, 8, 4, 7, 1, 5, 2,
    4, 5, 1, 6, 3, 2, 9, 7, 8,
    5, 4, 9, 1, 6, 8, 3, 2, 7,
    2, 1, 3, 5, 7, 9, 8, 6, 4,
    8, 6, 7, 3, 2, 4, 5, 9, 1,
    1, 2, 5, 4, 9, 3, 7, 8, 6,
    6, 3, 4, 7, 8, 5, 2, 1, 9,
    9, 7, 8, 2, 1, 6, 4, 3, 5
};

constexpr Details::ArrayType unsolved3{
    0, 0, 0, 0, 0, 7, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3, 0,
    0, 4, 5, 9, 0, 0, 0, 0, 1,
    0, 0, 2, 0, 0, 9, 0, 0, 0,
    0, 0, 4, 0, 3, 0, 0, 0, 6,
    7, 3, 0, 0, 2, 5, 0, 0, 9,
    0, 0, 0, 0, 0, 0, 0, 9, 0,
    9, 0, 0, 1, 0, 0, 0, 0, 3,
    1, 0, 0, 0, 0, 0, 0, 0, 5
};
constexpr Details::ArrayType solved3{
    3, 8, 9, 6, 1, 7, 4, 5, 2,
    6, 7, 1, 5, 4, 2, 9, 3, 8,
    2, 4, 5, 9, 8, 3, 7, 6, 1,
    5, 1, 2, 8, 6, 9, 3, 7, 4,
    8, 9, 4, 7, 3, 1, 5, 2, 6,
    7, 3, 6, 4, 2, 5, 8, 1, 9,
    4, 6, 3, 2, 5, 8, 1, 9, 7,
    9, 5, 8, 1, 7, 6, 2, 4, 3,
    1, 2, 7, 3, 9, 4, 6, 8, 5
};

constexpr Details::ArrayType unsolved4{
    0, 0, 0, 7, 8, 0, 0, 0, 0,
    0, 0, 0, 9, 0, 6, 0, 4, 0,
    3, 0, 0, 4, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 7, 0, 0, 9, 0,
    2, 0, 1, 0, 0, 9, 6, 0, 0,
    0, 0, 8, 0, 4, 1, 0, 7, 0,
    9, 6, 0, 0, 3, 0, 1, 0, 0,
    0, 4, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0
};
constexpr Details::ArrayType solved4{
    4, 2, 6, 7, 8, 3, 5, 1, 9,
    7, 1, 5, 9, 2, 6, 8, 4, 3,
    3, 8, 9, 4, 1, 5, 7, 6, 2,
    5, 3, 4, 6, 7, 8, 2, 9, 1,
    2, 7, 1, 3, 5, 9, 6, 8, 4,
    6, 9, 8, 2, 4, 1, 3, 7, 5,
    9, 6, 7, 5, 3, 4, 1, 2, 8,
    8, 4, 3, 1, 6, 2, 9, 5, 7,
    1, 5, 2, 8, 9, 7, 4, 3, 6
};

constexpr Details::ArrayType unsolved5{
    8, 0, 0, 9, 0, 0, 6, 0, 0,
    0, 0, 0, 0, 6, 0, 5, 3, 0,
    0, 7, 0, 0, 5, 3, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 5, 9,
    9, 0, 0, 8, 2, 0, 0, 1, 0,
    0, 0, 8, 1, 0, 9, 0, 2, 0,
    5, 0, 7, 0, 0, 2, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0
};
constexpr Details::ArrayType solved5{
    8, 5, 3, 9, 1, 4, 6, 7, 2,
    2, 1, 9, 7, 6, 8, 5, 3, 4,
    4, 7, 6, 2, 5, 3, 1, 9, 8,
    7, 8, 1, 3, 9, 5, 2, 4, 6,
    6, 3, 2, 4, 7, 1, 8, 5, 9,
    9, 4, 5, 8, 2, 6, 3, 1, 7,
    3, 6, 8, 1, 4, 9, 7, 2, 5,
    5, 9, 7, 6, 3, 2, 4, 8, 1,
    1, 2, 4, 5, 8, 7, 9, 6, 3
};

constexpr Details::ArrayType unsolved6{
    0, 3, 0, 0, 0, 0, 0, 2, 0,
    9, 0, 4, 1, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 7,
    0, 0, 0, 0, 3, 0, 0, 0, 0,
    1, 7, 0, 0, 4, 0, 0, 3, 6,
    0, 0, 2, 0, 0, 0, 0, 0, 0,
    2, 0, 6, 0, 0, 5, 0, 0, 3,
    0, 0, 0, 0, 0, 6, 0, 0, 5,
    0, 5, 0, 0, 7, 0, 2, 0, 0
};
constexpr Details::ArrayType solved6{
    8, 3, 7, 9, 5, 4, 6, 2, 1,
    9, 6, 4, 1, 2, 7, 3, 5, 8,
    5, 2, 1, 8, 6, 3, 4, 9, 7,
    6, 4, 5, 7, 3, 8, 9, 1, 2,
    1, 7, 9, 5, 4, 2, 8, 3, 6,
    3, 8, 2, 6, 1, 9, 5, 7, 4,
    2, 1, 6, 4, 9, 5, 7, 8, 3,
    7, 9, 3, 2, 8, 6, 1, 4, 5,
    4, 5, 8, 3, 7, 1, 2, 6, 9
};

constexpr Details::ArrayType unsolved7{
    0, 0, 0, 2, 0, 0, 0, 1, 0,
    7, 0, 0, 0, 0, 0, 6, 0, 0,
    0, 0, 4, 0, 0, 0, 9, 2, 5,
    0, 0, 1, 0, 4, 6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 6,
    2, 0, 0, 9, 0, 0, 0, 8, 0,
    0, 0, 0, 0, 0, 8, 7, 0, 0,
    0, 4, 9, 0, 0, 0, 0, 0, 1,
    0, 0, 5, 0, 0, 4, 0, 9, 0
};
constexpr Details::ArrayType solved7{
    9, 5, 8, 2, 6, 3, 4, 1, 7,
    7, 1, 2, 4, 5, 9, 6, 3, 8,
    6, 3, 4, 1, 8, 7, 9, 2, 5,
    5, 8, 1, 3, 4, 6, 2, 7, 9,
    4, 9, 7, 8, 2, 1, 3, 5, 6,
    2, 6, 3, 9, 7, 5, 1, 8, 4,
    1, 2, 6, 5, 9, 8, 7, 4, 3,
    8, 4, 9, 7, 3, 2, 5, 6, 1,
    3, 7, 5, 6, 1, 4, 8, 9, 2
};

constexpr Details::ArrayType unsolved8{
    6, 0, 0, 0, 0, 2, 0, 4, 0,
    8, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 6, 0, 0, 0,
    0, 0, 9, 0, 0, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 4, 7, 0, 2,
    0, 4, 0, 0, 9, 0, 5, 3, 0,
    0, 8, 0, 0, 3, 0, 0, 0, 0,
    5, 0, 0, 6, 0, 0, 2, 0, 0,
    0, 0, 3, 0, 8, 7, 4, 5, 0
};
constexpr Details::ArrayType solved8{
    6, 3, 5, 8, 1, 2, 9, 4, 7,
    8, 2, 4, 9, 7, 3, 6, 1, 5,
    9, 7, 1, 4, 5, 6, 3, 2, 8,
    7, 1, 9, 3, 2, 5, 8, 6, 4,
    3, 5, 8, 1, 6, 4, 7, 9, 2,
    2, 4, 6, 7, 9, 8, 5, 3, 1,
    4, 8, 2, 5, 3, 9, 1, 7, 6,
    5, 9, 7, 6, 4, 1, 2, 8, 3,
    1, 6, 3, 2, 8, 7, 4, 5, 9
};

constexpr Details::ArrayType unsolved9{
    0, 0, 0, 0, 9, 0, 0, 0, 0,
    0, 0, 2, 1, 0, 0, 3, 0, 8,
    0, 8, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 3, 0, 0, 5, 9, 0, 7,
    0, 0, 0, 6, 8, 0, 1, 0, 0,
    8, 0, 5, 9, 0, 0, 0, 0, 2,
    5, 0, 0, 0, 0, 1, 2, 0, 0,
    0, 0, 0, 0, 0, 6, 0, 5, 0,
    6, 3, 0, 0, 0, 0, 7, 0, 1
};
constexpr Details::ArrayType solved9{
    3, 7, 1, 5, 9, 8, 6, 2, 4,
    9, 5, 2, 1, 6, 4, 3, 7, 8,
    4, 8, 6, 3, 2, 7, 5, 1, 9,
    2, 6, 3, 4, 1, 5, 9, 8, 7,
    7, 9, 4, 6, 8, 2, 1, 3, 5,
    8, 1, 5, 9, 7, 3, 4, 6, 2,
    5, 4, 7, 8, 3, 1, 2, 9, 6,
    1, 2, 9, 7, 4, 6, 8, 5, 3,
    6, 3, 8, 2, 5, 9, 7, 4, 1
};

TEST_CASE("Row iteration") {
    SECTION("Can iterate from beginning of row") {
        Details::RowIterator iter0{solved0, Details::SudokuIdx{2}};
        REQUIRE(*iter0 == 4);
        iter0++;
        ++iter0;
        REQUIRE(*iter0 == 7);
        iter0 += Details::SudokuIdx{6};
        REQUIRE(*iter0 == 5);
        iter0 += Details::SudokuIdx{1};
        REQUIRE(*iter0 == 6);
    }

    SECTION("Can iterate from middle of row") {
        Details::RowIterator iter0{solved0, Details::SudokuIdx{2}};
        ++iter0;
        REQUIRE(*iter0 == 2);
        iter0++;
        ++iter0;
        REQUIRE(*iter0 == 1);
        iter0 += Details::SudokuIdx{6};
        REQUIRE(*iter0 == 6);
        iter0 += Details::SudokuIdx{1};
        REQUIRE(*iter0 == 3);
    }

    SECTION("Board idx to row idx works") {
        REQUIRE(Details::getRowIdx(Details::SudokuIdx{0}) == Details::SudokuIdx{0});
        REQUIRE(Details::getRowIdx(Details::SudokuIdx{1}) == Details::SudokuIdx{0});
        REQUIRE(Details::getRowIdx(Details::SudokuIdx{8}) == Details::SudokuIdx{0});
        REQUIRE(Details::getRowIdx(Details::SudokuIdx{9}) == Details::SudokuIdx{1});
        REQUIRE(Details::getRowIdx(Details::SudokuIdx{20}) == Details::SudokuIdx{2});
        REQUIRE(Details::getRowIdx(Details::SudokuIdx{81}) == Details::SudokuIdx{9});
    }

    SECTION("Row uniqueness is correct") {
        REQUIRE(Details::uniqueInRow(unsolved9, Details::SudokuIdx{0}, 1));
        REQUIRE(Details::uniqueInRow(unsolved9, Details::SudokuIdx{0}, 2));
        REQUIRE(not Details::uniqueInRow(unsolved9, Details::SudokuIdx{0}, 9));

        REQUIRE(not Details::uniqueInRow(solved9, Details::SudokuIdx{0}, 4));
        REQUIRE(not Details::uniqueInRow(solved9, Details::SudokuIdx{20}, 7));
    }
}

TEST_CASE("Column iteration") {

    SECTION("Can iterate from beginning of column") {
        Details::ColIterator iter0{solved0, Details::SudokuIdx{2}};
        REQUIRE(*iter0 == 6);
        iter0++;
        ++iter0;
        REQUIRE(*iter0 == 7);
        iter0 += Details::SudokuIdx{6};
        REQUIRE(*iter0 == 9);
        iter0 += Details::SudokuIdx{1};
        REQUIRE(*iter0 == 5);
    }

    SECTION("Can iterate from middle of column") {
        Details::ColIterator iter0{solved0, Details::SudokuIdx{2}};
        ++iter0;
        REQUIRE(*iter0 == 5);
        iter0++;
        ++iter0;
        REQUIRE(*iter0 == 1);
        iter0 += Details::SudokuIdx{6};
        REQUIRE(*iter0 == 5);
        iter0 += Details::SudokuIdx{1};
        REQUIRE(*iter0 == 7);
    }

    SECTION("Board idx to column idx works") {
        REQUIRE(Details::getColIdx(Details::SudokuIdx{0}) == Details::SudokuIdx{0});
        REQUIRE(Details::getColIdx(Details::SudokuIdx{1}) == Details::SudokuIdx{1});
        REQUIRE(Details::getColIdx(Details::SudokuIdx{8}) == Details::SudokuIdx{8});
        REQUIRE(Details::getColIdx(Details::SudokuIdx{9}) == Details::SudokuIdx{0});
        REQUIRE(Details::getColIdx(Details::SudokuIdx{20}) == Details::SudokuIdx{2});
        REQUIRE(Details::getColIdx(Details::SudokuIdx{81}) == Details::SudokuIdx{0});
    }

    SECTION("Column uniqueness is correct") {
        REQUIRE(Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 1));
        REQUIRE(Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 2));
        REQUIRE(not Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 5));
        REQUIRE(not Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 8));
        REQUIRE(not Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 6));

        REQUIRE(not Details::uniqueInCol(solved9, Details::SudokuIdx{0}, 4));
        REQUIRE(not Details::uniqueInCol(solved9, Details::SudokuIdx{20}, 7));
    }

}

} // namespace StaticSudoku::Test
