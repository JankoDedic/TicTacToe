#pragma once

#include <optional>

#include "Rectangle.hpp"
#include "Texture.hpp"

namespace TicTacToe {

class Sprite {
public:
    Sprite(Texture, Rectangle const& destinationBounds = Rectangle()) noexcept;

    auto destinationBounds() const noexcept -> Rectangle
    {
        return mDestinationBounds;
    }

    auto draw() const noexcept -> void;

protected:
    virtual auto sourceBounds() const noexcept -> std::optional<Rectangle>;

    Texture mTexture;
    Rectangle mDestinationBounds;
};

} // namespace TicTacToe
