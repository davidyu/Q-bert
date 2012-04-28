#include "ENTITY_cQubert.hpp"
#include <cmath>
#include "QCORE_cQGame.hpp"

/* temporary */ #include <iostream>
                using namespace std;

// sphere rendering code heavily based on that by Prof Carl Burch:
// http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/

using namespace ENTITY;

const float RADIUS = 7.5f;
const float Y_OFFSET = 15.0f;

const int LAT_RESOLUTION = 20;
const int LONG_RESOLUTION = 20;

const float QBERT_R = 1.0,
            QBERT_G = 0.5,
            QBERT_B = 0.0;

cQubert::cQubert(cPlayState* ps)
{
    _playState = ps;
    _qube = ps->GetQubeAt(0,0);
    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();
    _qube->activate();
    _color = Color(QBERT_R, QBERT_G, QBERT_B, 1.0f);
}

cQubert::cQubert(cPlayState* ps, cQube* q)
       : _playState(ps), _qube(q)
{
    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();
    _qube->activate();
    _color = Color(QBERT_R, QBERT_G, QBERT_B, 1.0f);
}

void cQubert::move(int i, int k)
{
    cout << _qube->getI() + i << ", " << _qube->getK() + k << endl;

    //map<pair<int, int>, vector<ENTITY::cQube*>*>::iterator it;

    _qube = _playState->GetQubeAt(_qube->getI() + i, _qube->getK() + k);

    if (_qube == 0) //death!
    {
        cout << "death!" << endl;
        _playState->ReportQubertDeath();
        _qube = _playState->GetDefaultQube();
    }

    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();

    _qube->activate();
}

void cQubert::update(CORE::cGame* game, float ticks)
{
    //cout << ticks << endl;
    //don't do anything here; input should be in cPlayState (by design)
    /*
    if (game->GetInput().GetKeyState(SDLK_LEFT))
        game->EndGame();
        */
}

void cQubert::render(float ticks)
{
    //cout << "called" << endl;
    //cout << percent_tick << endl;
    glPushMatrix();
    glTranslatef(_x, _y+Y_OFFSET, _z);

    int i, j;
    int latStrips = LAT_RESOLUTION;
    int longStrips = LONG_RESOLUTION;
    float r = RADIUS;

    for(i = 0; i <= latStrips; i++)
    {
        float lat0 = M_PI * (-0.5 + (float) (i - 1) / latStrips);
        float z0  = sin(lat0);
        float zr0 =  cos(lat0);

        float lat1 = M_PI * (-0.5 + (float) i / latStrips);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        glColor3f(_color.getR(), _color.getG(), _color.getB());
        for(j = 0; j <= longStrips; j++)
        {
            float lng = 2 * M_PI * (float) (j - 1) / longStrips;
            float x = cos(lng);
            float y = sin(lng);

            glNormal3f(x * zr0 * r, y * zr0 * r, z0 * r);
            glVertex3f(x * zr0 * r, y * zr0 * r, z0 * r);
            glNormal3f(x * zr1 * r, y * zr1 * r, z1 * r);
            glVertex3f(x * zr1 * r, y * zr1 * r, z1 * r);
        }
        glEnd();
    }

    glPopMatrix();

}
