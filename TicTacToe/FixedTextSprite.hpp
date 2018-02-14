#pragma once

#include <string>

#include "Color.hpp"
#include "Sprite.hpp"

namespace TicTacToe {

class FixedTextSprite : public Sprite {
public:
    FixedTextSprite(std::string const& text, Color textColor,
        Rectangle const& destinationBounds) noexcept;
};

} // namespace TicTacToe
