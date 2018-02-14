#include "Display.hpp"

#include <SDL2/SDL.h>

#include "Assert.hpp"

namespace TicTacToe {

auto getDisplaySize() noexcept -> Size
{
    SDL_Rect rect;
    if (SDL_GetDisplayUsableBounds(0, &rect) < 0) {
        SDL_assert(false);
    }
    return Size(rect.w, rect.h);
}

} // namespace TicTacToe
