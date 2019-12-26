#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace StaticSudoku {

namespace Details {

constexpr std::uint64_t NUM_TILES = 9;
constexpr std::uint64_t NUM_BOARD_TILES = NUM_TILES * NUM_TILES;

class SudokuIdx {
public:
    constexpr explicit SudokuIdx(std::uint64_t idx) : idx_{idx} {
        throwIfOOB();
    }

    [[nodiscard]] constexpr std::uint64_t value() const noexcept {
        return idx_;
    }

    friend constexpr SudokuIdx operator+(SudokuIdx lhs, SudokuIdx rhs) {
        SudokuIdx result{lhs.idx_ + rhs.idx_};
        result.throwIfOOB();
        return result;
    }

    friend constexpr SudokuIdx operator-(SudokuIdx lhs, SudokuIdx rhs) {
        SudokuIdx result{lhs.idx_ - rhs.idx_};
        result.throwIfOOB();
        return result;
    }

    friend constexpr SudokuIdx operator*(SudokuIdx lhs, std::uint64_t rhs) {
        SudokuIdx result{lhs.idx_ * rhs};
        result.throwIfOOB();
        return result;
    }

    friend constexpr SudokuIdx operator/(SudokuIdx lhs, std::uint64_t rhs) {
        SudokuIdx result{lhs.idx_ / rhs};
        result.throwIfOOB();
        return result;
    }

    friend constexpr SudokuIdx operator%(SudokuIdx lhs, std::uint64_t rhs) {
        SudokuIdx result{lhs.idx_ % rhs};
        result.throwIfOOB();
        return result;
    }

    friend constexpr SudokuIdx &operator++(SudokuIdx &idx) {
        ++idx.idx_;
        idx.throwIfOOB();
        return idx;
    }

    friend constexpr SudokuIdx &operator++(SudokuIdx &idx, int) {
        return operator++(idx);
    }

    friend constexpr SudokuIdx &operator+=(SudokuIdx &idx, SudokuIdx increase) {
        idx.idx_ += increase.idx_;
        return idx;
    }

    friend constexpr bool operator==(SudokuIdx lhs, SudokuIdx rhs) noexcept {
        return lhs.idx_ == rhs.idx_;
    }

    friend constexpr bool operator!=(SudokuIdx lhs, SudokuIdx rhs) noexcept {
        return lhs.idx_ != rhs.idx_;
    }

    friend constexpr bool operator<(SudokuIdx lhs, SudokuIdx rhs) noexcept {
        return lhs.idx_ < rhs.idx_;
    }

    friend constexpr bool operator<=(SudokuIdx lhs, SudokuIdx rhs) noexcept {
        return lhs.idx_ <= rhs.idx_;
    }

    friend constexpr bool operator>(SudokuIdx lhs, SudokuIdx rhs) noexcept {
        return lhs.idx_ > rhs.idx_;
    }

    friend constexpr bool operator>=(SudokuIdx lhs, SudokuIdx rhs) noexcept {
        return lhs.idx_ >= rhs.idx_;
    }

    template<typename OStreamT>
    friend OStreamT &operator<<(OStreamT &os, const SudokuIdx &rhs) {
        return os << "SudokuIdx{" << rhs.idx_ << "}";
    }

private:
    constexpr void throwIfOOB() const {
        if (idx_ >= NUM_BOARD_TILES) {
            //throw std::out_of_range{"Past end of board"};
        }
    }

    std::uint64_t idx_;
};

using TileType = std::uint64_t;
using ArrayType = std::array<TileType, NUM_BOARD_TILES>;

template<typename ToBoardIdxPolicyT, typename StepForwardPolicyT>
class SudokuIterator {
    friend StepForwardPolicyT;
public:
    constexpr SudokuIterator(const ArrayType &array, SudokuIdx bigIdx)
            : array_{array}, tileIdx_{ToBoardIdxPolicyT{}(bigIdx)}
    {
    }

    [[nodiscard]] SudokuIdx boardIdx() const {
        return tileIdx_;
    }

    friend constexpr const TileType &operator*(const SudokuIterator &iterator) {
        return iterator.array_.at(iterator.tileIdx_.value());
    }

    friend constexpr SudokuIterator &operator++(SudokuIterator &iterator) {
        iterator.tileIdx_ = StepForwardPolicyT{}(iterator.tileIdx_, SudokuIdx{1});
        return iterator;
    }

    friend constexpr SudokuIterator &operator++(SudokuIterator &iterator, int) {
        iterator.tileIdx_ = StepForwardPolicyT{}(iterator.tileIdx_, SudokuIdx{1});
        return iterator;
    }

    friend constexpr SudokuIterator &operator+=(SudokuIterator &iterator, SudokuIdx increase) {
        iterator.tileIdx_ = StepForwardPolicyT{}(iterator.tileIdx_, increase);
        return iterator;
    }

    friend constexpr SudokuIterator operator+(const SudokuIterator &iterator, SudokuIdx increase) {
        return SudokuIterator{iterator.array_, StepForwardPolicyT{}(iterator.tileIdx_, increase)};
    }

    friend constexpr bool operator==(const SudokuIterator &it1, const SudokuIterator &it2) noexcept {
        return it1.tileIdx_ == it2.tileIdx_;
    }

    friend constexpr bool operator!=(const SudokuIterator &it1, const SudokuIterator &it2) noexcept {
        return it1.tileIdx_ != it2.tileIdx_;
    }

    friend constexpr bool operator<(const SudokuIterator &it1, const SudokuIterator &it2) noexcept {
        return it1.tileIdx_ < it2.tileIdx_;
    }

    friend constexpr bool operator>(const SudokuIterator &it1, const SudokuIterator &it2) noexcept {
        return it1.tileIdx_ > it2.tileIdx_;
    }

    friend constexpr bool operator<=(const SudokuIterator &it1, const SudokuIterator &it2) noexcept {
        return it1.tileIdx_ <= it2.tileIdx_;
    }

    friend constexpr bool operator>=(const SudokuIterator &it1, const SudokuIterator &it2) noexcept {
        return it1.tileIdx_ >= it2.tileIdx_;
    }

private:
    const ArrayType &array_;
    SudokuIdx tileIdx_;
};

struct RowToBoardIdxPolicy {
    constexpr SudokuIdx operator()(SudokuIdx rowIdx) const {
        return rowIdx * NUM_TILES;
    }
};

struct RowStepForwardPolicy {
    constexpr SudokuIdx operator()(SudokuIdx currentBoardIdx, SudokuIdx increase) const {
        return currentBoardIdx + increase;
    }
};

using RowIterator = SudokuIterator<RowToBoardIdxPolicy, RowStepForwardPolicy>;

struct ColToBoardIdxPolicy {
    constexpr SudokuIdx operator()(SudokuIdx rowIdx) const {
        return rowIdx;
    }
};

struct ColStepForwardPolicy {
    constexpr SudokuIdx operator()(SudokuIdx currentBoardIdx, SudokuIdx increase) const {
        SudokuIdx resultBoardIdx = currentBoardIdx;
        for (std::uint64_t i = 0; i < increase.value(); ++i) {
            if (resultBoardIdx / 9 == SudokuIdx{8}) {
                resultBoardIdx = resultBoardIdx % 9 + SudokuIdx{1};
            } else {
                resultBoardIdx = resultBoardIdx + SudokuIdx{NUM_TILES};
            }
        }
        return resultBoardIdx;
    }
};

using ColIterator = SudokuIterator<ColToBoardIdxPolicy, ColStepForwardPolicy>;

struct BoxToBoardIdxPolicy {
    constexpr SudokuIdx operator()(SudokuIdx boxIdx) const {
        SudokuIdx boxColIdx{boxIdx % 3};
        SudokuIdx boxRowIdx{boxIdx.value() / 3};
        SudokuIdx result{boxRowIdx * 3 * NUM_TILES + boxColIdx * 3};
        return result;
    }
};

struct BoxStepForwardPolicy {
    constexpr SudokuIdx operator()(SudokuIdx currentBoardIdx, SudokuIdx increase) const {
        SudokuIdx resultBoardIdx = currentBoardIdx;
        for (std::uint64_t i = 0; i < increase.value(); ++i) {
            if ((resultBoardIdx % NUM_TILES) % 3 == SudokuIdx{2}) {
                const SudokuIdx resultBoardRow = resultBoardIdx / NUM_TILES;
                const SudokuIdx resultBoardCol = resultBoardIdx % NUM_TILES;
                const SudokuIdx resultBoxColIdx = (resultBoardIdx % 9) / 3;
                // If we are in the last position in the box
                if (resultBoardRow % 3 == SudokuIdx{2}) {
                    // If we are jumping to the next box row
                    if (resultBoxColIdx % 3 == SudokuIdx{2}) {
                        resultBoardIdx += SudokuIdx{1};
                    }
                    // If we are jumping to the next box in the same box row
                    else {
                        resultBoardIdx = (resultBoardRow - SudokuIdx{2}) * NUM_TILES + resultBoardCol + SudokuIdx{1};
                    }
                }
                // If we are in the last position in the first two box sub-rows
                else {
                    resultBoardIdx += SudokuIdx{7};
                }
            }
            // If we aren't in the last position in a box sub-row
            else {
                ++resultBoardIdx;
            }
        }
        return resultBoardIdx;
    }
};

using BoxIterator = SudokuIterator<BoxToBoardIdxPolicy, BoxStepForwardPolicy>;

/// Not constexpr until C++20
template<typename IterT, typename PredicateT>
constexpr bool all_of(IterT begin, IterT end, PredicateT predicate) {
    for (IterT it = begin; it != end; ++it) {
        if (not predicate(*begin)) {
            return false;
        }
    }
    return true;
}

/// Not constexpr until C++20
template<typename IterT, typename PredicateT>
constexpr bool none_of(IterT begin, IterT end, PredicateT predicate) {
    for (IterT it = begin; it != end; ++it) {
        if (predicate(*it)) {
            return false;
        }
    }
    return true;
}


constexpr bool tileValid(const TileType &tile) noexcept {
    return 1 <= tile and tile <= 9;
}

constexpr SudokuIdx getRowIdx(SudokuIdx boardIdx) noexcept {
    return boardIdx / NUM_TILES;
}

constexpr SudokuIdx getColIdx(SudokuIdx boardIdx) noexcept {
    return boardIdx % NUM_TILES;
}

constexpr SudokuIdx getBoxIdx(SudokuIdx boardIdx) noexcept {
    const SudokuIdx boxRowIdx = boardIdx / 27;
    const SudokuIdx boxColIdx = (boardIdx % 9) / 3;
    return boxRowIdx * 3 + boxColIdx;
}

constexpr bool uniqueInRow(const ArrayType &array, SudokuIdx idx, TileType proposedValue) {
    const SudokuIdx rowIdx = getRowIdx(idx);
    const RowIterator beginIter{array, rowIdx};
    const RowIterator endIter{array, rowIdx + SudokuIdx{1}};
    for (RowIterator iter = beginIter; iter != endIter; ++iter) {
        if (*iter == proposedValue and iter.boardIdx() != idx) {
            return false;
        }
    }
    return true;
}

constexpr bool uniqueInCol(const ArrayType &array, SudokuIdx idx, TileType proposedValue) {
    const SudokuIdx colIdx = getColIdx(idx);
    const ColIterator beginIter{array, colIdx};
    const ColIterator endIter{array, colIdx + SudokuIdx{1}};
    for (ColIterator iter = beginIter; iter != endIter; ++iter) {
        if (*iter == proposedValue and iter.boardIdx() != idx) {
            return false;
        }
    }
    return true;
}

constexpr bool uniqueInBox(const ArrayType &array, SudokuIdx idx, TileType proposedValue) {
    const SudokuIdx boxIdx = getBoxIdx(idx);
    const BoxIterator beginIter{array, boxIdx};
    const BoxIterator endIter{array, boxIdx + SudokuIdx{1}};
    for (BoxIterator iter = beginIter; iter != endIter; ++iter) {
        if (*iter == proposedValue and iter.boardIdx() != idx) {
            return false;
        }
    }
    return true;
}

constexpr bool isValidValueForIdx(const ArrayType &array, SudokuIdx idx, TileType proposedValue) {
    const bool validValue = tileValid(proposedValue);
    const bool validRow = uniqueInRow(array, idx, proposedValue);
    const bool validCol = uniqueInCol(array, idx, proposedValue);
    const bool validBox = uniqueInBox(array, idx, proposedValue);
    return validValue and validRow and validCol and validBox;
}

constexpr bool boardValid(const ArrayType &array) {
    const auto check = [&array] (auto rawIdx) {
        return isValidValueForIdx(array, SudokuIdx{rawIdx}, array.at(rawIdx));
    };
    return all_of(array.cbegin(), array.cend(), check);
}

using IsProvidedValueBitField = std::array<bool, NUM_BOARD_TILES>;

constexpr IsProvidedValueBitField getIsProvidedValueBitField(const ArrayType &array) {
    IsProvidedValueBitField result{false};
    for (std::uint64_t i = 0; i < array.size(); ++i) {
        result[i] = 1 <= array.at(i) and array.at(i) <= 9;
    }
    return result;
}

constexpr bool tryNumber(ArrayType &array, const IsProvidedValueBitField &isProvidedValue, SudokuIdx workingIdx, TileType tileToAttempt) {
    if (not isValidValueForIdx(array, workingIdx, tileToAttempt)) {
        return false;
    }
    array[workingIdx.value()] = tileToAttempt;

    SudokuIdx nextWorkingIdx = workingIdx + SudokuIdx{1};

    if (nextWorkingIdx >= SudokuIdx{NUM_BOARD_TILES}) {
        const bool isSolution = boardValid(array);
        if (not isSolution) {
            array[workingIdx.value()] = 0;
        }
        return isSolution;
    }

    while (isProvidedValue.at(nextWorkingIdx.value())) {
        ++nextWorkingIdx;
        if (nextWorkingIdx >= SudokuIdx{NUM_BOARD_TILES}) {
            const bool isSolution = boardValid(array);
            if (not isSolution) {
                array[workingIdx.value()] = 0;
            }
            return isSolution;
        }
    }

    for (TileType nextTileToAttempt = 1; nextTileToAttempt < 10; ++nextTileToAttempt) {
        if (tryNumber(array, isProvidedValue, nextWorkingIdx, nextTileToAttempt)) {
            return true;
        }
    }
    array[workingIdx.value()] = 0;
    return false;
}

} // namespace Details

constexpr Details::ArrayType constexprSolve(const Details::ArrayType &array) {
    Details::ArrayType attemptArray = array;
    Details::IsProvidedValueBitField isProvidedValue{true};
    isProvidedValue = Details::getIsProvidedValueBitField(array);

    Details::SudokuIdx nextWorkingIdx{0};
    while (isProvidedValue.at(nextWorkingIdx.value())) {
        ++nextWorkingIdx;
    }

    bool foundResult = false;
    for (Details::TileType nextTileToAttempt = 1; nextTileToAttempt < 10; ++nextTileToAttempt) {
        if (tryNumber(attemptArray, isProvidedValue, nextWorkingIdx, nextTileToAttempt)) {
            foundResult = true;
            break;
        }
    }
    return foundResult ? attemptArray : throw std::runtime_error{"No solution found"};
}

} // namespace StaticSudoku

