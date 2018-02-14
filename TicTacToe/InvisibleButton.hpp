#pragma once

#include "ButtonEventHandler.hpp"
#include "Observer.hpp"
#include "Rectangle.hpp"

namespace TicTacToe {

class InvisibleButton
    : public ButtonEventHandler
    , public Observable<InvisibleButton> {
public:
    using Event = ButtonEventHandler::Event;

    InvisibleButton() noexcept = default;

    InvisibleButton(Rectangle const& bounds) noexcept;

private:
    auto onPressSuccess() noexcept -> void final;

    auto hitbox() const -> Rectangle final;

    Rectangle mHitbox;
};

} // namespace TicTacToe
