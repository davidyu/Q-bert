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
    loadLevel();
    addQubert();
}

void cPlayState::loadLevel()
{
    //temporary
    int pyramid[49] = {1,2,3,4,5,6,7,
                       0,1,2,3,4,5,6,
                       0,0,1,2,3,4,5,
                       0,0,0,1,2,3,4,
                       0,0,0,0,1,2,3,
                       0,0,0,0,0,1,2,
                       0,0,0,0,0,0,1};

    int w = 7, h = 7;

    float cube_width  = 15,
          cube_height = 15,
          cube_depth  = 15;

    Color up(1.0f, 0, 0, 1.0f);
    Color activated(0.5f, 0.5f, 0, 1.0f);
    Color down(0, 1.0f, 0, 1.0f);
    Color left(0.3f, 0.3f, 0.3f, 1.0f);
    Color right(0, 1.0f, 1.0f, 1.0f);
    Color front(0, 0, 1.0f, 1.0f);
    Color back(0.3f, 0.3f, 0.3f, 1.0f);
    Color rest(0.3f, 0.3f, 0.3f, 1.0f);

    using std::vector;
    using std::map;
    using std::pair;
    using ENTITY::cQube;

    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            if(pyramid[j*w + i] >= 1)
            {
                vector<cQube*>* qubesHere = new vector<cQube*>();
                for (int k = 0; k < pyramid[j*w + i]; k++)
                {
                    cQube* q = new cQube(i*cube_width, k*cube_height, j*cube_height, cube_width, cube_depth, cube_height, j, k, i,
                                         up, activated, down, left, right, front, back);
                    entities.push_back(q);
                    qubesHere->push_back(q);
                }
                qubes.insert(make_pair(make_pair(j,i), qubesHere));
            }
        }
    }

    camera_x = 0; camera_y = 7 * cube_height; camera_z = 6 * cube_depth;
    _defaultQube = GetQubeAt(0, 6);

}

void cPlayState::addQubert()
{
    _qubert = new ENTITY::cQubert(this, GetQubeAt(0,6));
    entities.push_back(_qubert);
}

ENTITY::cQube* cPlayState::GetQubeAt(int i, int j)
{
    using std::vector; //need this!!!!!
    using std::map;
    using std::pair;
    using ENTITY::cQube;
    map<pair<int, int>, vector<ENTITY::cQube*>*>::iterator it;
    it = qubes.find(make_pair(i,j));

    if (it == qubes.end())
        return 0;

    vector<cQube*> v = *(*it).second;

    if (!v.empty())
        return v.back();
    else
        return 0;
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
    //cout << delta << endl;
    if (game->GetInput().GetKeyState(HAR_ESCAPE))
        game->EndGame();

    if (game->GetInput().OnKeyDown(HAR_LEFT))
        _qubert->move(-1,0);
    else if (game->GetInput().OnKeyDown(HAR_DOWN))
        _qubert->move(0,-1);
    else if (game->GetInput().OnKeyDown(HAR_RIGHT))
        _qubert->move(1,0);
    else if (game->GetInput().OnKeyDown(HAR_UP))
        _qubert->move(0,1);

    //update all entities
    using std::vector;
    using ENTITY::cEntity;
    for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        cEntity* e = *it;
        e->update(game, delta);
    }
}

//this takes the picture and plasters it
void RenderTexture(const cTexture& tex)
{
    glBindTexture(GL_TEXTURE_2D, tex.GetID());               // Select Our Texturek
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
    //cout << percent_tick << endl;
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
        e->render(percent_tick);
    }

   //start with camera
    GLfloat xtrans = -camera_x;
    GLfloat ytrans = -camera_y;
    GLfloat ztrans = -camera_z;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //isometric view!
    glRotatef(30.0, 1,0,0);
    glRotatef(45.0, 0,1,0); //usually -45 by convention, but Q*BERT wants 45
    glTranslatef(xtrans, ytrans, ztrans);
}

void cPlayState::HandleInput() {}

