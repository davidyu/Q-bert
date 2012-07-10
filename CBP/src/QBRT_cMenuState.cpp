#include <SDL2/SDL_opengl.h>
#include "QCORE_cQGame.hpp"
#include "QBRT_cMenuState.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "GFX_cImage.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_GfxHelper.hpp"


/*temp*/ #include <iostream>
         using namespace std;

using namespace GFX;
using namespace GFX::G2D;


cMenuState::cMenuState():swap(true), lastSwappedTick(-1) {}
cMenuState::~cMenuState() {}

STATE::iGameState* cMenuState::CreateInstance()
{
    return new cMenuState();
}

STATE::iGameState* cMenuState::Clone()
{
    return new cMenuState();
}

void cMenuState::Pause()
{}

void cMenuState::Resume()
{}

bool cMenuState::OnEnter()
{
    p_goScreen1 = new cTexture("art/menu_1.png");
    p_goScreen1->RegisterGL();

    p_goScreen2 = new cTexture("art/menu_2.png");
    p_goScreen2->RegisterGL();

    return true;
}

bool cMenuState::OnExit()
{
    glBindTexture(GL_TEXTURE_2D, NULL);
    delete p_goScreen1;
    delete p_goScreen2;
}

void cMenuState::Update(CORE::cGame* game, float delta)
{
    if (lastSwappedTick < 0)
        lastSwappedTick = (int)delta;

    if ((int)delta - lastSwappedTick >= 500)
    {
        swap = !swap;
        lastSwappedTick = delta;
    }

    if (game->GetInput().GetKeyState(HAR_ESCAPE))
        game->EndGame();
    else if (game->GetInput().GetKeyState(HAR_SPACE))
        game->GetStateManager().ReplaceState(game->state_factory.CreateObject("game"));
}

void cMenuState::Render(CORE::cGame* game, float percent_ticks)
{
    SDL_Rect viewport, temp_rect;
    SDL_Renderer* renderer = game->GetRenderer();
    SDL_RenderGetViewport(renderer, &viewport);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);

    //glClearColor (0.0, 0.0, 0.0, 0.0); - cooler this way
    glEnable(GL_ALPHA_TEST) ;
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    cTextureRegion scrn1 = cTextureRegion(*p_goScreen1);
    cTextureRegion scrn2 = cTextureRegion(*p_goScreen2);

    if (swap)
    {
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        ImmediateRenderTexturePos2Dim2(scrn1, -1, 1, 2, -2);
    }
    else
    {
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        ImmediateRenderTexturePos2Dim2(scrn2, -1, 1, 2, -2);
    }
}
