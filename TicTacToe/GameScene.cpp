#include "GameScene.hpp"

namespace TicTacToe {

auto GameScene::receiveEvent(GameView* gameView, GameView::Event const& event)
    noexcept -> void
{
    if (gameView == &mGameView) {
        if (event == GameView::Event::PauseButtonPressed) {
            mIsPauseDialogInFocus = true;
        }
    }
}

auto GameScene::receiveEvent(GamePauseDialog* pauseDialog,
    GamePauseDialog::Event const& event) noexcept -> void
{
    if (pauseDialog == &mGamePauseDialog) {
        switch (event) {
        case GamePauseDialog::Event::ResumeButtonPressed:
            mIsPauseDialogInFocus = false;
            break;
        case GamePauseDialog::Event::BackToMenuButtonPressed:
            notifyObserver(*this, Event::BackToMenuRequested);
            mIsPauseDialogInFocus = false;
            mGameView.resetBoard();
            break;
        default:
            break;
        }
    }
}

GameScene::GameScene() noexcept
{
    setObserver(mGameView, this);
    setObserver(mGamePauseDialog, this);
}

auto GameScene::handleEvent(SDL_Event const& event) noexcept -> void
{
    if (mIsPauseDialogInFocus) {
        mGamePauseDialog.handleEvent(event);
    } else {
        mGameView.handleEvent(event);
    }
}

auto GameScene::draw() const noexcept -> void
{
    mGameView.draw();
    if (mIsPauseDialogInFocus) {
        mGamePauseDialog.draw();
    }
}

} // namespace TicTacToe
