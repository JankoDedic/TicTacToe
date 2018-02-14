#pragma once

#include <array>

#include "Assert.hpp"
#include "Point.hpp"
#include "Score.hpp"

namespace TicTacToe {

enum class Mark {
    None, X, O
};

using Field = Point;

class Board {
public:
    Board() noexcept;

    auto operator[](Field const&) const noexcept -> Mark;

    auto operator[](Field const&) noexcept -> Mark&;

    auto reset() noexcept -> void;

private:
    std::array<std::array<Mark, 3>, 3> mFields;
};

class GameModel {
public:
    enum class Turn {
        X, O
    };

    GameModel() noexcept;

    auto turn() const noexcept -> Turn;

    auto isGameOver() const noexcept -> bool;

    auto board() const noexcept -> Board const&;

    auto xScore() const noexcept -> Score;

    auto oScore() const noexcept -> Score;

    // Callable only if `isGameOver() == false;`
    auto mark(Field) noexcept -> void;

    auto reset() noexcept -> void;

    // Callable only if `isGameOver() == true;`
    auto winningLine() const noexcept -> std::pair<Field, Field>;

private:
    auto checkForWinner() noexcept -> void;

    Board mBoard;
    Turn mTurn;
    bool mIsGameOver = false;
    Score mXScore;
    Score mOScore;
    std::pair<Field, Field> mWinningLine;
};

} // namespace TicTacToe
