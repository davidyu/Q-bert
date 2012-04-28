#include <SDL2/SDL_opengl.h>
#include "QCORE_cQGame.hpp"
#include "QBRT_cGameOverState.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "GFX_cImage.hpp"
#include "GFX_cTexture.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_GfxHelper.hpp"


/*temp*/ #include <iostream>
         using namespace std;

using namespace GFX;
using namespace GFX::G2D;

enum State
{
    JUST_OVER,    //just shows "game over" screen
    GIVE_REPRIEVE //shows "press r to restart"
};

const int REPRIEVE_THRESH = 1000;

cTexture* p_goScreen1;
cTexture* p_goScreen2;

cGameOverState::cGameOverState():m_ticksSinceGameOver(-1), m_state(JUST_OVER) {}
cGameOverState::~cGameOverState() {}

STATE::iGameState* cGameOverState::CreateInstance()
{
    return new cGameOverState;
}

STATE::iGameState* cGameOverState::Clone()
{
    return new cGameOverState;
}

void cGameOverState::Pause()
{}

void cGameOverState::Resume()
{}

bool cGameOverState::OnEnter()
{
    cout << "Game over!" << endl;
    m_state = JUST_OVER;

    p_goScreen1 = new cTexture("art/game_over_1.png");
    p_goScreen1->RegisterGL();

    p_goScreen2 = new cTexture("art/game_over_2.png");
    p_goScreen2->RegisterGL();

    return true;
}

bool cGameOverState::OnExit()
{
    glBindTexture(GL_TEXTURE_2D, NULL);
    delete p_goScreen1;
    delete p_goScreen2;
}

void cGameOverState::Update(CORE::cGame* game, float delta)
{
    if (m_ticksSinceGameOver == -1)
    {
        m_ticksSinceGameOver = (int) delta;
        return;
    }

    if ((int)delta - m_ticksSinceGameOver >= REPRIEVE_THRESH)
        m_state = GIVE_REPRIEVE;

    if (game->GetInput().GetKeyState(HAR_ESCAPE))
        game->EndGame();
    else if (game->GetInput().GetKeyState(HAR_r))
        game->GetStateManager().ReplaceState(game->state_factory.CreateObject("game"));
}

void cGameOverState::Render(CORE::cGame* game, float percent_ticks)
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
    if (m_state == JUST_OVER)
    {
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        ImmediateRenderTexturePos2Dim2(scrn1, -0.75f, 0.75f, 1.5f, -1.5f);
    }
    else
    {
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        ImmediateRenderTexturePos2Dim2(scrn2, -0.75f, 0.75f, 1.5f, -1.5f);
    }
}
