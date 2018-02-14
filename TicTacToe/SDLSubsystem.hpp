#pragma once

namespace TicTacToe {

class SDLSubsystem {
public:
    static auto initialize() noexcept -> void;

private:
    SDLSubsystem() noexcept;

    ~SDLSubsystem();
};

} // namespace TicTacToe
