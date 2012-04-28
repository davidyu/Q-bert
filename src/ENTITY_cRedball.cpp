#include "ENTITY_cRedball.hpp"
#include <cmath>

using namespace ENTITY;

/* temporary */ #include <iostream>
                using namespace std;

enum State {
    JUMPING,
    IDLE,
    THINKING,
    DEAD
};

const float RADIUS = 5.0f;
const float Y_OFFSET = 10.0f;

const int LAT_RESOLUTION = 20;
const int LONG_RESOLUTION = 20;

cRedball::cRedball(cPlayState* ps, cQube* q, int startTick)
       : _qube(q), _playState(ps), _executeStrategyThresh(1000), _ticksSinceExecuteStrategy(startTick)
{
    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();
    _color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    _state = IDLE;
    srand(time(NULL));
}

void cRedball::update(CORE::cGame* game, float ticks)
{
    if (_state == DEAD)
        return;

    if (ticks - _ticksSinceExecuteStrategy >= _executeStrategyThresh)
    {
        //move somewhere
        int r = rand() % 2;
        if (r == 0 && (_qube->getJ() - 1 > 0 || _qube->getJ() == 0)) //left
        {
            move(0, -1);
        }
        else if (_qube->getI() + 1 < 6 || _qube->getI() == 6)        //right
        {
            move(1, 0);
        }
        _ticksSinceExecuteStrategy = ticks;
    }
}

void cRedball::move(int i, int k)
{
    _qube = _playState->GetQubeAt(_qube->getI() + i, _qube->getK() + k);

    if (_qube == 0) //death!
    {
        cout << "red ball death!" << endl;
        _playState->Remove(this);
        _state = DEAD;
        return;
    }

    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();

    _qube->activate();
}

void cRedball::render(float ticks)
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
