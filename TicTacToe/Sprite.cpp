#include "Sprite.hpp"

#include "Renderer.hpp"

namespace TicTacToe {

Sprite::Sprite(Texture texture, Rectangle const& destinationBounds) noexcept
    : mTexture(std::move(texture))
    , mDestinationBounds(destinationBounds)
{
}

auto Sprite::draw() const noexcept -> void
{
    Renderer::instance().copy(mTexture, sourceBounds(), mDestinationBounds);
}

auto Sprite::sourceBounds() const noexcept -> std::optional<Rectangle>
{
    return std::nullopt;
}

} // namespace TicTacToe
