#pragma once

#include <array>

#include "FixedTextSprite.hpp"
#include "GameModel.hpp"
#include "GameViewButton.hpp"
#include "Grid.hpp"
#include "InvisibleButton.hpp"
#include "ScoreSprite.hpp"
#include "Sprite.hpp"

namespace TicTacToe {

class GameView
    : public Observable<GameView>
    , public Observer<GameViewButton>
    , public Observer<InvisibleButton> {
public:
    enum class Event {
        PauseButtonPressed
    };

    auto receiveEvent(GameViewButton*, GameViewButton::Event const&) noexcept
        -> void override;

    auto receiveEvent(InvisibleButton*, InvisibleButton::Event const&) noexcept
        -> void override;

    GameView() noexcept;

    auto resetBoard() noexcept -> void;

    auto handleEvent(SDL_Event const&) noexcept -> void;

    auto draw() const noexcept -> void;

private:
    auto initializeBoardButtons() noexcept -> void;

    auto performButtonPress(int row, int column) noexcept -> void;

    auto drawMarks() const noexcept -> void;

    GameModel mModel;
    Sprite mBackground;
    GameViewButton mPauseButton;
    FixedTextSprite mXScoreTitleSprite;
    ScoreSprite mXScoreSprite;
    FixedTextSprite mOScoreTitleSprite;
    ScoreSprite mOScoreSprite;
    Sprite mBoardFrameSprite;
    Grid mBoardGrid;
    Texture mXTexture;
    Texture mOTexture;
    std::array<std::array<InvisibleButton, 3>, 3> mBoardButtons;
};

} // namespace TicTacToe
