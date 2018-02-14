#include "InvisibleButton.hpp"

namespace TicTacToe {

InvisibleButton::InvisibleButton(Rectangle const& bounds) noexcept
    : mHitbox(bounds)
{
}

auto InvisibleButton::hitbox() const -> Rectangle
{
    return mHitbox;
}

auto InvisibleButton::onPressSuccess() noexcept -> void
{
    notifyObserver(*this, Event::PressSuccess);
}

} // namespace TicTacToe
