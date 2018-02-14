#pragma once

namespace TicTacToe {

class IMGSubsystem {
public:
    static auto initialize() noexcept -> void;

private:
    IMGSubsystem() noexcept;

    ~IMGSubsystem();
};

} // namespace TicTacToe
