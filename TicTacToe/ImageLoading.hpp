#pragma once

#include <string>

#include "Texture.hpp"

namespace TicTacToe {

auto loadTexture(std::string const& path) noexcept -> Texture;

} // namespace TicTacToe
