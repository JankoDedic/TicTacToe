#pragma once

namespace TicTacToe {

class TTFSubsystem {
public:
    static auto initialize() noexcept -> void;

private:
    TTFSubsystem() noexcept;

    ~TTFSubsystem();
};

} // namespace TicTacToe
