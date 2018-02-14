#include "GameModel.hpp"

#include <algorithm>
#include <iostream>

namespace TicTacToe {

Board::Board() noexcept
{
    reset();
}

auto Board::operator[](Field const& field) const noexcept -> Mark
{
    SDL_assert(0 <= field.x()); SDL_assert(field.x() <= 2);
    SDL_assert(0 <= field.y()); SDL_assert(field.y() <= 2);
    return mFields[field.x()][field.y()];
}

auto Board::operator[](Field const& field) noexcept -> Mark&
{
    SDL_assert(0 <= field.x()); SDL_assert(field.x() <= 2);
    SDL_assert(0 <= field.y()); SDL_assert(field.y() <= 2);
    return mFields[field.x()][field.y()];
}

auto Board::reset() noexcept -> void
{
    for (auto& row : mFields) {
        for (auto& item : row) {
            item = Mark::None;
        }
    }
}

GameModel::GameModel() noexcept
    : mTurn(Turn::X)
{
}

auto GameModel::turn() const noexcept -> Turn
{
    return mTurn;
}

auto GameModel::isGameOver() const noexcept -> bool
{
    return mIsGameOver;
}

auto GameModel::board() const noexcept -> Board const&
{
    return mBoard;
}

auto GameModel::xScore() const noexcept -> Score
{
    return mXScore;
}

auto GameModel::oScore() const noexcept -> Score
{
    return mOScore;
}

auto GameModel::mark(Field field) noexcept -> void
{
    SDL_assert(!isGameOver());
    SDL_assert(mBoard[field] == Mark::None);
    mBoard[field] = mTurn == Turn::X ? Mark::X : Mark::O;
    mTurn = mTurn == Turn::X ? Turn::O : Turn::X;
    checkForWinner();
}

auto GameModel::reset() noexcept -> void
{
    //SDL_assert(isGameOver());
    mBoard.reset();
    mIsGameOver = false;
}

auto GameModel::winningLine() const noexcept -> std::pair<Field, Field>
{
    SDL_assert(isGameOver());
    return mWinningLine;
}

static auto areAllRowFieldsMarked(Board const& board, int row) noexcept -> bool
{
    return !(board[Field(row, 0)] == Mark::None
        || board[Field(row, 1)] == Mark::None
        || board[Field(row, 2)] == Mark::None);
}

static auto areAllColumnFieldsMarked(Board const& board, int column) noexcept
    -> bool
{
    return !(board[Field(0, column)] == Mark::None
        || board[Field(1, column)] == Mark::None
        || board[Field(2, column)] == Mark::None);
}

static auto areRowMarksEqual(Board const& board, int row) noexcept -> bool
{
    return board[Field(row, 0)] == board[Field(row, 1)]
        && board[Field(row, 1)] == board[Field(row, 2)];
}

static auto areColumnMarksEqual(Board const& board, int column) noexcept
    -> bool
{
    return board[Field(0, column)] == board[Field(1, column)]
        && board[Field(1, column)] == board[Field(2, column)];
}

static auto areFirstDiagonalFieldsMarked(Board const& board) noexcept -> bool
{
    return !(board[Field(0, 0)] == Mark::None
        || board[Field(1, 1)] == Mark::None
        || board[Field(2, 2)] == Mark::None);
}

static auto areSecondDiagonalFieldsMarked(Board const& board) noexcept -> bool
{
    return !(board[Field(2, 0)] == Mark::None
        || board[Field(1, 1)] == Mark::None
        || board[Field(0, 2)] == Mark::None);
}

static auto areAllFieldsMarked(Board const& board) noexcept -> bool
{
    for (int row(0); row < 3; ++row) {
        for (int column(0); column < 3; ++column) {
            if (board[Field(row, column)] == Mark::None) {
                return false;
            }
        }
    }
    return true;
}

auto GameModel::checkForWinner() noexcept -> void
{
    auto playerWon = [this]() {
        mIsGameOver = true;
        if (mBoard[mWinningLine.first] == Mark::X) {
            mXScore.increment();
        } else {
            mOScore.increment();
        }
    };
    // Check all rows
    for (int row(0); row < 3; ++row) {
        if (!areAllRowFieldsMarked(mBoard, row)) {
            continue;
        }
        if (areRowMarksEqual(mBoard, row)) {
            mWinningLine = std::make_pair(Field(row, 0), Field(row, 2));
            playerWon();
            return;
        }
    }
    // Check all columns
    for (int column(0); column < 3; ++column) {
        if (!areAllColumnFieldsMarked(mBoard, column)) {
            continue;
        }
        if (areColumnMarksEqual(mBoard, column)) {
            mWinningLine = std::make_pair(Field(0, column), Field(2, column));
            playerWon();
            return;
        }
    }
    // Check both diagonals
    if (areFirstDiagonalFieldsMarked(mBoard)) {
        // TODO: areFirstDiagonalFieldsEqual()
        if (mBoard[Field(0, 0)] == mBoard[Field(1, 1)]
            && mBoard[Field(1, 1)] == mBoard[Field(2, 2)]) {
            mWinningLine = std::make_pair(Field(0, 0), Field(2, 2));
            playerWon();
            return;
        }
    }
    if (areSecondDiagonalFieldsMarked(mBoard)) {
        // TODO: areSecondDiagonalFieldsEqual()
        if (mBoard[Field(2, 0)] == mBoard[Field(1, 1)]
            && mBoard[Field(1, 1)] == mBoard[Field(0, 2)]) {
            mWinningLine = std::make_pair(Field(2, 0), Field(0, 2));
            playerWon();
            return;
        }
    }
    // In case of a draw
    if (areAllFieldsMarked(mBoard)) {
        mIsGameOver = true;
    }
}

} // namespace TicTacToe
