#include <SDL2/SDL_opengl.h>
#include "QBRT_cPlayState.hpp"
#include "QCORE_cQGame.hpp"
#include "GFX_cTexture.hpp"

#define SHADED_CUBE

/*temp*/ #include <iostream>
         using namespace std;

using namespace GFX;


cPlayState::cPlayState() {}
cPlayState::~cPlayState() {}

STATE::iGameState* cPlayState::CreateInstance()
{
    return new cPlayState;
}
STATE::iGameState* cPlayState::Clone()
{
    return new cPlayState;
}

cTexture* p_tex = 0;

bool cPlayState::OnEnter()
{
    p_tex = new cTexture("test.png");
    p_tex->RegisterGL();

    loadLevel();
}

void cPlayState::loadLevel()
{
    //temporary
    bool pyramid[25] = {1,1,1,1,1,
                      0,1,1,1,1,
                      0,0,1,1,1,
                      0,0,0,1,1,
                      0,0,0,0,1};

    int w = 5, h = 5;

    int cube_width = 2, cube_height = 2, cube_depth = 2;

    Color up(1.0f, 0.0f, 0.0f, 1.0f);
    Color rest(1.0f, 1.0f, 1.0f, 1.0f);

    using std::vector; //need this!!!!!
    using ENTITY::cQube;
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            if(pyramid[j*w + i])
            {
                cQube* q = new cQube(i*cube_width, 0, j*cube_height, cube_width, cube_depth, cube_height, up, rest);
                entities.push_back(q);
            }
        }
    }
}

bool cPlayState::OnExit()
{
    delete p_tex;
    p_tex = 0;
}
void cPlayState::Pause() {}
void cPlayState::Resume() {}

void cPlayState::Update(CORE::cGame* game, float delta)
{
    if (game->GetInput().GetKeyState(HAR_ESCAPE)) game->EndGame();
}
static void
Rander()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(1.0, 1.0, 1.0, 1.0);
}

//this takes the picture and plasters it
void RenderTexture(const cTexture& tex)
{
    glBindTexture(GL_TEXTURE_2D, tex.GetID());               // Select Our Texture
    glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  2.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  2.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -2.0f,  1.0f);
	glEnd();
}

void cPlayState::Render(CORE::cGame* game, float percent_tick)
{
    SDL_Rect viewport, temp_rect;
    SDL_Renderer* renderer = game->GetRenderer();
    SDL_RenderGetViewport(renderer, &viewport);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //RenderTexture(*p_tex);


    using std::vector;
    using ENTITY::cEntity;
    for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        cEntity* e = *it;
        e->render();
    }

    //Rander();
}

void cPlayState::HandleInput() {}

