#include "GameView.hpp"

#include "ImageLoading.hpp"
#include "RectangleFunctions.hpp"
#include "Renderer.hpp"

namespace TicTacToe {

constexpr char const* backgroundTexturePath("Assets/Background.png");
static Rectangle const backgroundBounds(0, 0, 1080, 1920);

constexpr char const* pauseButtonTexturePath("Assets/pause.png");
static Rectangle const pauseButtonBounds(960, 20, 100, 100);

constexpr char const* xScoreTitleText("X score:");
constexpr Color xScoreTitleColor(255, 255, 255);
static Rectangle const xScoreTitleBounds(0, 0, 540, 144);

constexpr Color xScoreNumberColor(255, 255, 255);
static Rectangle const xScoreNumberBounds(540, 0, 540, 144);

constexpr char const* oScoreTitleText("O score:");
constexpr Color oScoreTitleColor(255, 255, 255);
static Rectangle const oScoreTitleBounds(0, 144, 540, 144);

constexpr Color oScoreNumberColor(255, 255, 255);
static Rectangle const oScoreNumberBounds(540, 144, 540, 144);

constexpr char const* boardFrameTexturePath("Assets/BoardFrame.png");
static Rectangle const boardFrameBounds(0, 288, 1080, 1920 - 288);

static auto getBoardFrameSprite() noexcept -> Sprite
{
    auto boardFrameTexture = loadTexture(boardFrameTexturePath);
    auto boardFrameTextureDestination = fittingRectangle(
        boardFrameTexture.size(), boardFrameBounds);
    scaleInPlace(boardFrameTextureDestination, 0.9);
    return Sprite(std::move(boardFrameTexture), boardFrameTextureDestination);
}

constexpr char const* xTexturePath("Assets/X.png");

constexpr char const* oTexturePath("Assets/O.png");

auto GameView::receiveEvent(GameViewButton* button,
    GameViewButton::Event const& event) noexcept -> void
{
    if (button == &mPauseButton) {
        if (event == GameViewButton::Event::PressSuccess) {
            notifyObserver(*this, Event::PauseButtonPressed);
        }
    }
}

auto GameView::receiveEvent(InvisibleButton* invisibleButton,
    InvisibleButton::Event const& event) noexcept -> void
{
    if (mModel.isGameOver()) {
        mModel.reset();
        return;
    }
    for (int row(0); row < 3; ++row) {
        for (int column(0); column < 3; ++column) {
            if (invisibleButton == &mBoardButtons[row][column]) {
                performButtonPress(row, column);
            }
        }
    }
}

GameView::GameView() noexcept
    : mBackground(loadTexture(backgroundTexturePath), backgroundBounds)
    , mPauseButton(loadTexture(pauseButtonTexturePath), pauseButtonBounds)
    , mXScoreTitleSprite(xScoreTitleText, xScoreTitleColor, xScoreTitleBounds)
    , mXScoreSprite(xScoreNumberColor, xScoreNumberBounds)
    , mOScoreTitleSprite(oScoreTitleText, oScoreTitleColor, oScoreTitleBounds)
    , mOScoreSprite(oScoreNumberColor, oScoreNumberBounds)
    , mBoardFrameSprite(getBoardFrameSprite())
    , mBoardGrid(mBoardFrameSprite.destinationBounds(), 3, 3, 20)
    , mXTexture(loadTexture(xTexturePath))
    , mOTexture(loadTexture(oTexturePath))
{
    setObserver(mPauseButton, this);
    initializeBoardButtons();
}

auto GameView::resetBoard() noexcept -> void
{
    mModel.reset();
}

auto GameView::handleEvent(SDL_Event const& event) noexcept -> void
{
    mPauseButton.handleEvent(event);
    for (int row(0); row < 3; ++row) {
        for (int column(0); column < 3; ++column) {
            mBoardButtons[row][column].handleEvent(event);
        }
    }
}

auto GameView::draw() const noexcept -> void
{
    mBackground.draw();
    mPauseButton.draw();
    mXScoreTitleSprite.draw();
    mXScoreSprite.draw();
    mOScoreTitleSprite.draw();
    mOScoreSprite.draw();
    Renderer::instance().setDrawColor(Color(0, 0, 0, 144));
    Renderer::instance().fill(mBoardFrameSprite.destinationBounds());
    mBoardFrameSprite.draw();
    drawMarks();
}

auto GameView::initializeBoardButtons() noexcept -> void
{
    for (int row(0); row < 3; ++row) {
        for (int column(0); column < 3; ++column) {
            mBoardButtons[row][column] = mBoardGrid.fieldBounds(row, column);
            setObserver(mBoardButtons[row][column], this);
        }
    }
}

auto GameView::performButtonPress(int row, int column) noexcept -> void
{
    if (mModel.board()[Field(row, column)] == Mark::None) {
        mModel.mark(Field(row, column));
        if (mModel.isGameOver()) {
            mXScoreSprite.setScore(mModel.xScore());
            mOScoreSprite.setScore(mModel.oScore());
        }
    }
}

auto GameView::drawMarks() const noexcept -> void
{
    for (int row(0); row < 3; ++row) {
        for (int column(0); column < 3; ++column) {
            if (mModel.board()[Field(row, column)] == Mark::X) {
                Renderer::instance().copy(mXTexture, std::nullopt,
                    mBoardGrid.fieldBounds(row, column));
            } else if (mModel.board()[Field(row, column)] == Mark::O) {
                Renderer::instance().copy(mOTexture, std::nullopt,
                    mBoardGrid.fieldBounds(row, column));
            }
        }
    }
}

} // namespace TicTacToe
