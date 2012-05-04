#include <SDL2/SDL_opengl.h>
#include "QBRT_cPlayState.hpp"
#include "STATE_iGameState.hpp"
#include "QCORE_cQGame.hpp"
#include "GFX_cTexture.hpp"
#include "QBRT_cPauseState.hpp"
#include <cmath>

/*temp*/ #include <iostream>
         using namespace std;

using namespace GFX;
using namespace CORE;
using namespace STATE;

float camera_x, camera_y, camera_z;
float rot_x, rot_y, rot_z;

float multiplier = 1.0f;

enum QubertGameState {
    QUBERT_HAS_WON,
    QUBERT_IS_DYING,
    QUBERT_IS_FINE
};

cPlayState:: cPlayState()
           : m_xTheta(0), m_yTheta(0), _addEnemyThresh(3000), _lastEnemyGenTick(-1), _qubertGameState(QUBERT_IS_FINE),
             CELEBRATION_THRESHOLD(2000)
{
}

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
    cout << "new game" << endl;
    loadLevel();
    addQubert();
    resetSDLView(); //need to reenable depth and ortho view after game over
}

void cPlayState::resetSDLView()
{
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -500.0f, 500.0f);

    //lighting
    /*
    GLfloat mat_specular[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat mat_shininess[] = {0.0001};
    GLfloat light_position[] = {20, 20, 20};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat global_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);


    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    GLfloat la[] = { 1.0 };
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, la);
    GLfloat light_position[] = {20, 20, 20};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    */

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
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

    /*
    int pyramid[49] = {1,2,3,4,7,6,10,
                       0,1,4,3,4,5,6,
                       0,0,1,2,7,4,5,
                       0,0,0,1,2,3,14,
                       0,0,0,0,1,2,3,
                       0,0,0,0,0,3,2,
                       0,0,0,0,0,0,1};
    */

    int w = 7, h = 7;

    float cube_width  = 15,
          cube_height = 15,
          cube_depth  = 15;

    Color up(0.90f, 0.82f, 0, 1.0f);
    Color activated(0.32f, 0.32f, 0.99f, 1.0f);
    Color down(0, 1.0f, 0, 1.0f);
    Color left(0.30f, 0.63f, 0.59f, 1.0f);
    Color right(0.19f, 0.26f, 0.26f, 1.0f);
    Color front(0, 0, 1.0f, 1.0f);
    Color back(0.3f, 0.3f, 0.3f, 1.0f);
    Color rest(0.3f, 0.3f, 0.3f, 1.0f);

    using std::vector;
    using std::map;
    using std::pair;
    using ENTITY::cQube;

    //pyramid construction
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

    _qubesActivated = 0;

    camera_x = 0; camera_y = 7 * cube_height; camera_z = 6 * cube_depth;
    _defaultQube = GetQubeAt(0, 6);

}

void cPlayState::addQubert()
{
    _qubert = new ENTITY::cQubert(this, GetQubeAt(0,6));
    _qubertLives = 3;
    entities.push_back(_qubert);
}

void cPlayState::addEnemy(float now)
{
    using ENTITY::cRedball;
    using ENTITY::cQube;
    srand(time(NULL));
    cQube* startingQube;

    int r = rand() % 2;
    if (r == 0)
        startingQube = GetQubeAt(0, 5);
    else
        startingQube = GetQubeAt(1, 6);

    cRedball* rb = new cRedball(this, startingQube, (int)now);
    entities.push_back(rb);
    enemies.push_back(rb);
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

//deletes all enemies and puts qubert at the top of the pyramid
void cPlayState::Restart()
{
    using std::vector;
    using ENTITY::cEntity;
    for(vector<cEntity*>::iterator eit = enemies.begin(); eit != enemies.end(); ++eit)
    {
        cEntity* e = *eit;
        //O(n^2) linear search; find the enemy in the larger entities vector and remove him.
        for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
        {
            cEntity* ee = *it;
            if (ee == e)
            {
                delete e;
                entities.erase(it);
                break;
            }
        }
    }
    enemies.clear();
    _qubertGameState = QUBERT_IS_FINE;
}

void cPlayState::MoveCamera(float xrot, float yrot)
{
    m_xTheta = xrot;
    m_yTheta = yrot;
}

void cPlayState::Remove(ENTITY::cEntity* e) //removes entity
{
    using std::vector;
    using ENTITY::cEntity;
    for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        cEntity* ee = *it;
        if (ee == e)
        {
            entities.erase(it);
            break;
        }
    }

    for(vector<cEntity*>::iterator eit = enemies.begin(); eit != enemies.end(); ++eit)
    {
        cEntity* ee = *eit;
        if (ee == e)
        {
            enemies.erase(eit);
            break;
        }
    }

    delete e;
}

void cPlayState::ReportQubertDeath()
{
    _qubertLives--;
}

void cPlayState::ReportQubeActivation()
{
    _qubesActivated++;
    if (_qubesActivated >= qubes.size())
    {
        _qubertGameState = QUBERT_HAS_WON;
        _tickAtVictory = -1;
    }
}

bool cPlayState::OnExit()
{
    using std::vector;
    using ENTITY::cEntity;

    for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        cEntity* e = *it;
        delete e;
    }

    entities.clear();
    enemies.clear();
}

void cPlayState::Pause() {}
void cPlayState::Resume()
{
    resetSDLView();
}

void cPlayState::Update(CORE::cGame* game, float delta)
{
    if (game->GetInput().GetKeyState(HAR_ESCAPE))
        game->EndGame();

    if (_qubertGameState == QUBERT_IS_DYING) //only update qubert
    {
        _qubert->update(game, delta);
        return; //temporarily stop updating everything else
    }
    else if (_qubertGameState == QUBERT_HAS_WON) //celebrate!
    {
        if (_tickAtVictory < 0)
            _tickAtVictory = (int) delta;

        multiplier = 0.3 * sin(0.01 * delta) + 0.7;

        if ((int) delta - _tickAtVictory >= CELEBRATION_THRESHOLD) //reset game
        {
            multiplier = 1.0f; //reset to eliminate global varibale artifacting
            game->GetStateManager().ReplaceState(game->state_factory.CreateObject("game"));
        }

        return;
    }

    //collision detection logic
    using ENTITY::cQube;
    using ENTITY::cRedball;
    using std::vector;
    using ENTITY::cEntity;

    cQube* c = _qubert->getQube();
    if (c != 0)
    {
        for(vector<cEntity*>::iterator eit = enemies.begin(); eit != enemies.end(); ++eit)
        {
            cRedball* e = (cRedball*) *eit;
            if (e->getQube() == c)
            {
                _qubert->handleCollision(delta);
                _qubertGameState = QUBERT_IS_DYING;
            }
        }
    }

    //qubert movement logic
    if (game->GetInput().OnKeyDown(HAR_LEFT))
        _qubert->move(-1,0);
    else if (game->GetInput().OnKeyDown(HAR_DOWN))
        _qubert->move(0,-1);
    else if (game->GetInput().OnKeyDown(HAR_RIGHT))
        _qubert->move(1,0);
    else if (game->GetInput().OnKeyDown(HAR_UP))
        _qubert->move(0,1);

    if (game->GetInput().OnKeyDown(HAR_p))
        game->GetStateManager().PushState(new cPauseState(this));

    //add new enemies
    if (_lastEnemyGenTick < 0)
        _lastEnemyGenTick = (int) delta;

    if (delta - _lastEnemyGenTick >= _addEnemyThresh)
    {
        addEnemy(delta);
        _lastEnemyGenTick = delta;
    }

    //update all entities
    using std::vector;
    using ENTITY::cEntity;
    for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        cEntity* e = *it;
        e->update(game, delta);
    }

    if (_qubertLives <= 0) //game over!
        game->GetStateManager().ReplaceState(game->state_factory.CreateObject("game_over"));
}

void cPlayState::Render(CORE::cGame* game, float percent_tick)
{
    glLoadIdentity();
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -500.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //change camera to right place
    glRotatef(30.0, 1,0,0);
    glRotatef(45.0, 0,1,0); //usually -45 by convention, but Q*BERT wants 45

    glRotatef(-m_xTheta, 0, 1, 0);
    glRotatef(-m_yTheta, 1, 0, 0);

    GLfloat xtrans = -camera_x;
    GLfloat ytrans = -camera_y;
    GLfloat ztrans = -camera_z;

    glTranslatef(xtrans, ytrans, ztrans);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    using std::vector;
    using ENTITY::cEntity;
    for(vector<cEntity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        cEntity* e = *it;
        e->render(percent_tick);
    }

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
}

void cPlayState::HandleInput() {}
