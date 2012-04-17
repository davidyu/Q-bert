#include <iostream>
#include "QCORE_cQGame.hpp"

/* Include windows.h properly on Windows */
#if defined(WIN32) || defined(_WINDOWS)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

/* SDL */
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#ifndef HELLO_MAGIC_MAIN
#  undef main
#endif


using namespace CORE;

// Main function must have these params for SDL... kinda lame for encapsulation here..
int main(int argc, char* args[])
{
    iApplication* game = new cGame();

     if (game->Initialise()) {
        game->MainLoop();
        game->Terminate();
     }


    delete game;

    return 0;
}
