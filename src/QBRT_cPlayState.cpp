#include <SDL2/SDL_opengl.h>
#include "QBRT_cPlayState.hpp"
#include "QCORE_cQGame.hpp"
#include "GFX_cTexture.hpp"

#define SHADED_CUBE

/*temp*/ #include <iostream>
         using namespace std;

using namespace GFX;

float camera_x, camera_y, camera_z;
float rot_x, rot_y, rot_z;

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

    float cube_width = 5, cube_height = 5, cube_depth = 5;

    Color up(1.0f, 0, 0, 1.0f);
    Color down(0, 1.0f, 0, 1.0f);
    Color left(0.3f, 0.3f, 0.3f, 1.0f);
    Color right(0, 1.0f, 1.0f, 1.0f);
    Color front(0, 0, 1.0f, 1.0f);
    Color back(0.3f, 0.3f, 0.3f, 1.0f);
    Color rest(0.3f, 0.3f, 0.3f, 1.0f);

    using std::vector; //need this!!!!!
    using ENTITY::cQube;
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            if(pyramid[j*w + i] == 1)
            {
                cQube* q = new cQube(i*cube_width, 0, j*cube_height, cube_width, cube_depth, cube_height,
                                     up, down, left, right, front, back);
                entities.push_back(q);
            }
        }
    }

    camera_x = 0; camera_y = cube_height * 2; camera_z = 5 * cube_depth;

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

    using std::vector;
    using ENTITY::cEntity;
    for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        cEntity* e = *it;
        e->render();
    }

   //start with camera

    GLfloat xtrans = -camera_x;
    GLfloat ytrans = -camera_y;
    GLfloat ztrans = -camera_z;

    GLfloat xrot = 360 - rot_x;
    GLfloat yrot = 360 - rot_y;
    GLfloat zrot = 360 - rot_z;

    //iso
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glRotatef(0.1, 1.0, 1.0, 1.0);
    glRotatef(30.0, 1,0,0);
    glRotatef(-45.0, 0,1,0);

    glTranslatef(xtrans, ytrans, .0f);

    //Rander();
}

void cPlayState::HandleInput() {}

