#include "Grid.hpp"

namespace TicTacToe {

Grid::Grid(Rectangle const& bounds, int rows, int columns, int padding)
    noexcept
    : mBounds(bounds)
    , mFieldSize((bounds.width() - columns*padding) / columns,
        (bounds.height() - rows*padding) / rows)
    , mPadding(padding)
{
}

auto Grid::fieldBounds(int x, int y) const noexcept -> Rectangle
{
    // TODO: Assert to ensure valid arguments are passed in.
    return Rectangle(
        mBounds.x() + mPadding + x * (mFieldSize.width() + mPadding),
        mBounds.y() + mPadding + y * (mFieldSize.height() + mPadding),
        mFieldSize);
}

} // namespace TicTacToe
