#include "SDL_Wrappers.h"
#include <iostream>

void DLAB_UTIL::SDL_Destroyer::operator()(SDL_Window* window) const
{
	SDL_DestroyWindow(window);
	std::cout << "SDL_Window destroyed\n";

}

void DLAB_UTIL::SDL_Destroyer::operator()(SDL_GameController* controller) const
{
}

void DLAB_UTIL::SDL_Destroyer::operator()(SDL_Cursor* cursor) const
{
}

Controller make_shared_controller(SDL_GameController* controller)
{
    return Controller();
}

Cursor make_shared_cursor(SDL_Cursor* cursor)
{
    return Cursor();
}
