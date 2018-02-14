#pragma once

#include <string>

#include "Color.hpp"
#include "Texture.hpp"

namespace TicTacToe {

auto getTextTexture(std::string const& text, Color) noexcept -> Texture;

} // namespace TicTacToe
