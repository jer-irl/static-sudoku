#include "boards.hpp"
#include "catch.hpp"
#include <StaticSudoku/constexpr.hpp>

namespace StaticSudoku::Test {

TEST_CASE("constexpr row iteration") {
    SECTION("Can iterate from beginning of row") {
        Details::RowIterator iter0{solved0, Details::SudokuIdx{2}};
        CHECK(*iter0 == 4);
        iter0++;
        ++iter0;
        CHECK(*iter0 == 7);
        iter0 += Details::SudokuIdx{6};
        CHECK(*iter0 == 5);
        iter0 += Details::SudokuIdx{1};
        CHECK(*iter0 == 6);
    }

    SECTION("Can iterate from middle of row") {
        Details::RowIterator iter0{solved0, Details::SudokuIdx{2}};
        ++iter0;
        CHECK(*iter0 == 2);
        iter0++;
        ++iter0;
        CHECK(*iter0 == 1);
        iter0 += Details::SudokuIdx{6};
        CHECK(*iter0 == 6);
        iter0 += Details::SudokuIdx{1};
        CHECK(*iter0 == 3);
    }

    SECTION("Board idx to row idx works") {
        CHECK(Details::getRowIdx(Details::SudokuIdx{0}) == Details::SudokuIdx{0});
        CHECK(Details::getRowIdx(Details::SudokuIdx{1}) == Details::SudokuIdx{0});
        CHECK(Details::getRowIdx(Details::SudokuIdx{8}) == Details::SudokuIdx{0});
        CHECK(Details::getRowIdx(Details::SudokuIdx{9}) == Details::SudokuIdx{1});
        CHECK(Details::getRowIdx(Details::SudokuIdx{20}) == Details::SudokuIdx{2});
        CHECK(Details::getRowIdx(Details::SudokuIdx{81}) == Details::SudokuIdx{9});
    }

    SECTION("Row uniqueness is correct") {
        CHECK(Details::uniqueInRow(unsolved9, Details::SudokuIdx{0}, 1));
        CHECK(Details::uniqueInRow(unsolved9, Details::SudokuIdx{0}, 2));
        CHECK(not Details::uniqueInRow(unsolved9, Details::SudokuIdx{0}, 9));

        CHECK(not Details::uniqueInRow(solved9, Details::SudokuIdx{0}, 4));
        CHECK(not Details::uniqueInRow(solved9, Details::SudokuIdx{20}, 7));
    }
}

TEST_CASE("constexpr column iteration") {
    SECTION("Can iterate from beginning of column") {
        Details::ColIterator iter0{solved0, Details::SudokuIdx{2}};
        CHECK(*iter0 == 6);
        iter0++;
        ++iter0;
        CHECK(*iter0 == 7);
        iter0 += Details::SudokuIdx{6};
        CHECK(*iter0 == 9);
        iter0 += Details::SudokuIdx{1};
        CHECK(*iter0 == 5);
    }

    SECTION("Can iterate from middle of column") {
        Details::ColIterator iter0{solved0, Details::SudokuIdx{2}};
        ++iter0;
        CHECK(*iter0 == 5);
        iter0++;
        ++iter0;
        CHECK(*iter0 == 1);
        iter0 += Details::SudokuIdx{6};
        CHECK(*iter0 == 5);
        iter0 += Details::SudokuIdx{1};
        CHECK(*iter0 == 7);
    }

    SECTION("Board idx to column idx works") {
        CHECK(Details::getColIdx(Details::SudokuIdx{0}) == Details::SudokuIdx{0});
        CHECK(Details::getColIdx(Details::SudokuIdx{1}) == Details::SudokuIdx{1});
        CHECK(Details::getColIdx(Details::SudokuIdx{8}) == Details::SudokuIdx{8});
        CHECK(Details::getColIdx(Details::SudokuIdx{9}) == Details::SudokuIdx{0});
        CHECK(Details::getColIdx(Details::SudokuIdx{20}) == Details::SudokuIdx{2});
        CHECK(Details::getColIdx(Details::SudokuIdx{81}) == Details::SudokuIdx{0});
    }

    SECTION("Column uniqueness is correct") {
        CHECK(Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 1));
        CHECK(Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 2));
        CHECK(not Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 5));
        CHECK(not Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 8));
        CHECK(not Details::uniqueInCol(unsolved9, Details::SudokuIdx{0}, 6));

        CHECK(not Details::uniqueInCol(solved9, Details::SudokuIdx{0}, 4));
        CHECK(not Details::uniqueInCol(solved9, Details::SudokuIdx{20}, 7));
    }
}

TEST_CASE("constexpr box iteration") {
    SECTION("Can iterate from beginning of box") {
        Details::BoxIterator iter0{solved0, Details::SudokuIdx{2}};
        CHECK(*iter0 == 4);
        iter0++;
        ++iter0;
        CHECK(*iter0 == 1);
        iter0 += Details::SudokuIdx{6};
        CHECK(*iter0 == 5);
        iter0 += Details::SudokuIdx{1};
        CHECK(*iter0 == 6);
        iter0 += Details::SudokuIdx{9};
        CHECK(*iter0 == 8);
    }

    SECTION("Can iterate from middle of box") {
        Details::BoxIterator iter0{solved0, Details::SudokuIdx{2}};
        ++iter0;
        CHECK(*iter0 == 7);
        iter0++;
        ++iter0;
        CHECK(*iter0 == 6);
        iter0 += Details::SudokuIdx{6};
        CHECK(*iter0 == 6);
        iter0 += Details::SudokuIdx{1};
        CHECK(*iter0 == 3);
    }

    SECTION("Board idx to box idx works") {
        CHECK(Details::getBoxIdx(Details::SudokuIdx{0}) == Details::SudokuIdx{0});
        CHECK(Details::getBoxIdx(Details::SudokuIdx{1}) == Details::SudokuIdx{0});
        CHECK(Details::getBoxIdx(Details::SudokuIdx{8}) == Details::SudokuIdx{2});
        CHECK(Details::getBoxIdx(Details::SudokuIdx{9}) == Details::SudokuIdx{0});
        CHECK(Details::getBoxIdx(Details::SudokuIdx{20}) == Details::SudokuIdx{0});
        CHECK(Details::getBoxIdx(Details::SudokuIdx{27}) == Details::SudokuIdx{3});
        CHECK(Details::getBoxIdx(Details::SudokuIdx{80}) == Details::SudokuIdx{8});
        CHECK(Details::getBoxIdx(Details::SudokuIdx{81}) == Details::SudokuIdx{9});
    }

    SECTION("Box uniqueness is correct") {
        CHECK(Details::uniqueInBox(unsolved9, Details::SudokuIdx{0}, 1));
        CHECK(Details::uniqueInBox(unsolved9, Details::SudokuIdx{0}, 3));
        CHECK(not Details::uniqueInBox(unsolved9, Details::SudokuIdx{0}, 2));

        CHECK(not Details::uniqueInBox(solved9, Details::SudokuIdx{0}, 4));
        CHECK(Details::uniqueInBox(solved9, Details::SudokuIdx{20}, 6));
    }
}

TEST_CASE("Constexpr board validity check") {
    CHECK(Details::boardValid(solved0));
    CHECK(Details::boardValid(solved1));
    CHECK(Details::boardValid(solved2));
    CHECK(Details::boardValid(solved3));
    CHECK(Details::boardValid(solved4));
    CHECK(Details::boardValid(solved5));
    CHECK(Details::boardValid(solved6));
    CHECK(Details::boardValid(solved7));
    CHECK(Details::boardValid(solved8));
    CHECK(Details::boardValid(solved9));
    CHECK(not Details::boardValid(unsolved0));
    CHECK(not Details::boardValid(unsolved1));
    CHECK(not Details::boardValid(unsolved2));
    CHECK(not Details::boardValid(unsolved3));
    CHECK(not Details::boardValid(unsolved4));
    CHECK(not Details::boardValid(unsolved5));
    CHECK(not Details::boardValid(unsolved6));
    CHECK(not Details::boardValid(unsolved7));
    CHECK(not Details::boardValid(unsolved8));
    CHECK(not Details::boardValid(unsolved9));
}

TEST_CASE("Solving with constexpr") {
    CHECK(constexprSolve(unsolved0) == solved0);
    CHECK(constexprSolve(unsolved1) == solved1);
    CHECK(constexprSolve(unsolved2) == solved2);
    CHECK(constexprSolve(unsolved3) == solved3);
    CHECK(constexprSolve(unsolved4) == solved4);
    CHECK(constexprSolve(unsolved5) == solved5);
    CHECK(constexprSolve(unsolved6) == solved6);
    CHECK(constexprSolve(unsolved7) == solved7);
    CHECK(constexprSolve(unsolved8) == solved8);
    CHECK(constexprSolve(unsolved9) == solved9);
}

} // namespace StaticSudoku::Test
