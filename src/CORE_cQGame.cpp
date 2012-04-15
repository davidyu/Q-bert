#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include "CORE_cGame.hpp"
#include "STATE_iGameState.hpp"
#include "demo_cPlayState.hpp"



/*temp*/ #include <iostream>
         #include <cassert>
        using namespace std;

using namespace CORE;
using namespace STATE;

cGame::cGame()
: m_sdl_state(0)
{
}

cGame::~cGame()
{
    //dtor
}
#include <stdlib.h>
bool cGame::Initialise()
{
    if (!SDL_Init( SDL_INIT_EVERYTHING )){
        return false;
    }
    if (!IMG_Init( IMG_INIT_PNG )){
        printf("IMG_Init: %s\n", IMG_GetError());
//        return false ;
    }
    m_running = true;
    // Setup SDL Window and Render
    m_sdl_state = new cSDLState();
    m_sdl_state->window = SDL_CreateWindow(m_sdl_state->window_title,
        m_sdl_state->window_x,
        m_sdl_state->window_y,
        m_sdl_state->window_w , m_sdl_state->window_h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    // Fullscreen?
    SDL_SetWindowFullscreen(m_sdl_state->window, m_sdl_state->is_fullscreen);
    // Renderer
    m_sdl_state->renderer = SDL_CreateRenderer(m_sdl_state->window,
                                    0, m_sdl_state->render_flags);
    // GL Context
    m_sdl_state->glctx = SDL_GL_CreateContext(m_sdl_state->window);
    SDL_GL_MakeCurrent(m_sdl_state->window, m_sdl_state->glctx);

    SDL_GL_SetSwapInterval(1); // 1 for Vsync?

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, 3.0, -3.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);

                           // Enable Texture Mapping ( NEW )
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective


    m_input.Initialise();

    state_factory.RegisterClass("game", cPlayState::CreateInstance);
    m_state_manager.PushState(state_factory.CreateObject("game"));

    return true;
}

bool cGame::Terminate()
{
    if (m_sdl_state) {

        if (m_sdl_state->renderer) {
            SDL_DestroyRenderer(m_sdl_state->renderer);
        }
        if (m_sdl_state->glctx)    {
            SDL_GL_DeleteContext(m_sdl_state->glctx);
        }
        if (m_sdl_state->window)   {
            SDL_DestroyWindow(m_sdl_state->window);
        }
        SDL_free(m_sdl_state);
    }
    SDL_Quit();
    IMG_Quit();
}

void cGame::MainLoop()
{
    iGameState* state;
    float delta, percent_tick; // Dummy vars for now; substitute timer values in later

    while (m_running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                EndGame();
            }
        }
        // Update Input-- set old keystates and current ones
        m_input.Update();

        // Game Loop
        state = m_state_manager.GetCurrent();
        /*DEBUG*/assert(state!=0);
        state->Update(this, delta);


        state->Render(this, percent_tick);

        SDL_GL_SwapWindow(m_sdl_state->window);
        //SDL_RenderPresent(m_sdl_state->renderer); // Gets overwritten somehow by SwapWindow
    }
    m_state_manager.ClearAll();
}

void cGame::EndGame()
{
    m_running = false;
}

Input& cGame::GetInput()
{
    return m_input;
}
cGameStateManager& cGame::GetStateManager()
{
    return m_state_manager;
}


