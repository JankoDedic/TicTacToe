#include "MenuSceneView.hpp"

#include "Color.hpp"
#include "Font.hpp"
#include "ImageLoading.hpp"
#include "Renderer.hpp"

namespace TicTacToe {

auto MenuSceneView::receiveEvent(Button* pButton, Button::Event const& event)
    noexcept -> void
{
    if (pButton == &mStartButton) {
        if (event == Button::Event::PressSuccess) {
            notifyObserver(*this, Event::StartButtonPressed);
        }
    } else if (pButton = &mCreditsButton) {
        if (event == Button::Event::PressSuccess) {
            notifyObserver(*this, Event::CreditsButtonPressed);
        }
    }
}

constexpr char const* backgroundSpriteTexturePath("Assets/MenuBackground.png");
static Rectangle const backgroundSpriteBounds(0, 0, 1080, 1920);

constexpr char const* gameTitleText("Tic-Tac-Toe");
constexpr Color gameTitleTextColor(255, 201, 14);
static Rectangle const gameTitleBounds(40, 1050, 1000, 400);

static auto getGameTitleSprite() noexcept -> FixedTextSprite
{
    Font::instance().setOutline(6);
    FixedTextSprite sprite(gameTitleText, gameTitleTextColor, gameTitleBounds);
    Font::instance().setOutline(0);
    Font::instance().setStyle(Font::Style::Normal);
    return sprite;
}

constexpr char const* startButtonNormalTexturePath(
    "Assets/buttonStartNormal.png");
constexpr char const* startButtonMouseoverTexturePath(
    "Assets/buttonStartBubble.png");
constexpr char const* startButtonHoldTexturePath(
    "Assets/buttonStartInvert.png");
static Rectangle const startButtonBounds(140, 1450, 800, 200);

constexpr char const* creditsButtonNormalTexturePath(
    "Assets/buttonCreditsNormal.png");
constexpr char const* creditsButtonMouseoverTexturePath(
    "Assets/buttonCreditsBubble.png");
constexpr char const* creditsButtonHoldTexturePath(
    "Assets/buttonCreditsInvert.png");
static Rectangle const creditsButtonBounds(290, 1675, 500, 125);

MenuSceneView::MenuSceneView() noexcept
    : mBackgroundSprite(loadTexture(backgroundSpriteTexturePath),
        backgroundSpriteBounds)
    , mGameTitleSprite(getGameTitleSprite())
    , mStartButton(loadTexture(startButtonNormalTexturePath),
        loadTexture(startButtonMouseoverTexturePath),
        loadTexture(startButtonHoldTexturePath), startButtonBounds)
    , mCreditsButton(loadTexture(creditsButtonNormalTexturePath),
        loadTexture(creditsButtonMouseoverTexturePath),
        loadTexture(creditsButtonHoldTexturePath), creditsButtonBounds)
{
    setObserver(mStartButton, this);
    setObserver(mCreditsButton, this);
}

auto MenuSceneView::handleEvent(SDL_Event const& event) noexcept -> void
{
    mStartButton.handleEvent(event);
    mCreditsButton.handleEvent(event);
}

constexpr Color backgroundColor(15, 15, 15);

auto MenuSceneView::draw() const noexcept -> void
{
    Renderer::instance().setDrawColor(backgroundColor);
    Renderer::instance().clear();
    mBackgroundSprite.draw();
    mGameTitleSprite.draw();
    mStartButton.draw();
    mCreditsButton.draw();
}

} // namespace TicTacToe
