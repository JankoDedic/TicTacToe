#pragma once

#include "Rectangle.hpp"
#include "Size.hpp"

namespace TicTacToe {

class Grid {
public:
    Grid() noexcept = default;

    Grid(Rectangle const& bounds, int rows, int columns, int padding) noexcept;

    auto fieldBounds(int x, int y) const noexcept -> Rectangle;

private:
    Rectangle mBounds;
    Size mFieldSize;
    int mPadding;
};

} // namespace TicTacToe
