#include <SDL2/SDL_opengl.h>
#include "QCORE_cQGame.hpp"
#include "QBRT_cPauseState.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "GFX_cImage.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_GfxHelper.hpp"


/*temp*/ #include <iostream>
         using namespace std;

using namespace GFX;
using namespace GFX::G2D;

const int SCREEN_W = 1024;
const int SCREEN_H = 960;


cPauseState::cPauseState(cPlayState* ps)
            :swap(true), lastSwappedTick(-1), xrot(0), yrot(0), MOVE_EPSILON(1)
{
    _playState = ps;
}

//do NOT use these!!!
cPauseState::cPauseState()
            :swap(true), lastSwappedTick(-1), xrot(0), yrot(0), MOVE_EPSILON(1) {}

cPauseState::~cPauseState() {}

STATE::iGameState* cPauseState::CreateInstance()
{
    return new cPauseState();
}

STATE::iGameState* cPauseState::Clone()
{
    return new cPauseState();
}

void cPauseState::Pause()
{}

void cPauseState::Resume()
{}

bool cPauseState::OnEnter()
{
    p_pause = new cTexture("art/pause.png");
    p_pause->RegisterGL();

    return true;
}

bool cPauseState::OnExit()
{
    glBindTexture(GL_TEXTURE_2D, NULL);
    delete p_pause;
}

void cPauseState::Update(CORE::cGame* game, float delta)
{
    if (lastSwappedTick < 0)
        lastSwappedTick = (int)delta;

    if ((int)delta - lastSwappedTick >= 500)
    {
        swap = !swap;
        lastSwappedTick = delta;
    }

    //camera movement logic
    if (game->GetInput().GetKeyState(HAR_LEFT))
        xrot -= MOVE_EPSILON;
    else if (game->GetInput().GetKeyState(HAR_DOWN))
        yrot += MOVE_EPSILON;
    else if (game->GetInput().GetKeyState(HAR_RIGHT))
        xrot += MOVE_EPSILON;
    else if (game->GetInput().GetKeyState(HAR_UP))
        yrot -= MOVE_EPSILON;

    if (game->GetInput().GetKeyState(HAR_ESCAPE))
        game->EndGame();

    else if (game->GetInput().OnKeyDown(HAR_p))
        game->GetStateManager().PopState();

}

void cPauseState::Render(CORE::cGame* game, float percent_ticks)
{

    _playState->MoveCamera(xrot, yrot);
    _playState->Render(game, percent_ticks);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0.0f, (float)SCREEN_W, (float)SCREEN_H, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);

    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_ALPHA_TEST) ;
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    if (swap)
    {
        cTextureRegion scrn1 = cTextureRegion(*p_pause);
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        ImmediateRenderTexturePos2Dim2(scrn1, -0.625f, 0.625f, 1.25f, -1.25f);
        glBindTexture(GL_TEXTURE_2D, NULL);
    }

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

}
