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

cRedball::cRedball(cPlayState* ps, cQube* q, int startTick)
       : _spline(0), _qube(q), _playState(ps), _executeStrategyThresh(1000), _ticksSinceExecuteStrategy(startTick),
         RADIUS(5.0f), Y_OFFSET(10.0f), LAT_RESOLUTION(20), LONG_RESOLUTION(20), JUMP_TIME(500)
{
    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();
    _color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    _state = IDLE;
    srand(time(NULL));
}

void cRedball::move(int i, int k)
{
    cQube* nQ = _playState->GetQubeAt(_qube->getI() + i, _qube->getK() + k);

    if (nQ == 0) //death!
    {
        cout << "a red ball just fell into the abyss!" << endl;
        _state = DEAD;
        _playState->Remove(this);
        return;
    }

    float nx = nQ->getX();
    float ny = nQ->getY();
    float nz = nQ->getZ();

    float dx = nx - _x,
          dy = ny - _y,
          dz = nz - _z;

    using MATH::Vec3f;

    const int JUMP_HEIGHT = 2.0;
    Vec3f p0(_x, _y, _z);
    Vec3f p1(nx, ny, nz);
    Vec3f p1_p0 = p1 - p0;
    p1_p0.Normalize();
    Vec3f p0p(p1_p0.x, 50, p1_p0.z);
    Vec3f p1p(p1_p0.x, -50, p1_p0.z);

    _nextQube = nQ;
    _qube = 0;

    if (_spline != 0)
        delete _spline;

    using MATH::Spline;
    _spline = new Spline(p0, p1, p0p, p1p);
    _state = JUMPING;
    m_tickAtJumpGather = -1;
}

void cRedball::update(CORE::cGame* game, float ticks)
{
    if (_state == DEAD)
        return;
    else if (_state == JUMPING)
    {
        if (m_tickAtJumpGather < 0)
            m_tickAtJumpGather = ticks;

        float u = (ticks - m_tickAtJumpGather) / JUMP_TIME;

        if (u >= 1)
        {
            _qube = _nextQube;

            if (_qube == 0)
                return; //DEAD!

            _x = _qube->getX();
            _y = _qube->getY();
            _z = _qube->getZ();

            _state = IDLE;
            return;
        }

        using MATH::Vec3f;
        Vec3f pos = _spline->getPosHermite(u);

        _x = pos.x;
        _y = pos.y;
        _z = pos.z;
    }
    else if (_state == IDLE && (ticks - _ticksSinceExecuteStrategy >= _executeStrategyThresh))
    {
        //move somewhere
        int r = rand() % 2;
        if (r == 0 && _qube->getJ() > 0) //left
        {
            move(0, -1);
        }
        else if (_qube->getI() < 6)        //right
        {
            move(1, 0);
        }
        _ticksSinceExecuteStrategy = ticks;
    }
}

void cRedball::render(float ticks)
{
    if (_state == DEAD)
        return;
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
