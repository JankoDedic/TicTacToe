#include "SDLSubsystem.hpp"
#include "IMGSubsystem.hpp"
#include "TTFSubsystem.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

#include "Game.hpp"

namespace TicTacToe {

auto Main() noexcept -> void
{
    SDLSubsystem::initialize();
    IMGSubsystem::initialize();
    TTFSubsystem::initialize();
    Window::instance();
    Renderer::instance();
    Game game;
    SDL_Event event;
    bool isRunning(true);
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            game.handleEvent(event);
        }
        Renderer::instance().setDrawColor(Color(0, 0, 0, 255));
        Renderer::instance().clear();
        game.draw();
        Renderer::instance().present();
    }
}

} // namespace TicTacToe

auto main(int argc, char* argv[]) -> int
{
    TicTacToe::Main();
    return 0;
}