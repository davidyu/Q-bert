#include "ENTITY_cQubert.hpp"
#include <cmath>
#include "QCORE_cQGame.hpp"

#include "GFX_cImage.hpp"
#include "GFX_cTexture.hpp"
#include "GFX_G2D_cTextureRegion.hpp"
#include "GFX_cTextureRegistry.hpp"
#include "GFX_G2D_cAnimation.hpp"
#include "GFX_GfxHelper.hpp"

#include "MATH_Vec3.hpp"

/* temporary */ #include <iostream>
                using namespace std;

// sphere rendering code heavily based on that by Prof Carl Burch:
// http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/

enum State {
    JUMPING,
    IDLE,
    JUMPING_TO_DEATH,
    CURSING,
    DEAD
};

using namespace ENTITY;
using namespace GFX;
using namespace GFX::G2D;

const float RADIUS = 7.5f;
const float Y_OFFSET = 15.0f;

const float SPEECH_W = 15.0f;
const float SPEECH_H = 10.0f;

const int LAT_RESOLUTION = 20;
const int LONG_RESOLUTION = 20;

const float QBERT_R = 1.0,
            QBERT_G = 0.5,
            QBERT_B = 0.0;

cTexture* p_expletives = 0;

cQubert::cQubert(cPlayState* ps)
        : _spline(0), m_state(IDLE), DEATH_COOLDOWN(1000), JUMP_TIME(500)
{
    _playState = ps;
    _qube = ps->GetQubeAt(0,0);
    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();

    if (_qube->activate())
        ps->ReportQubeActivation();

    _color = Color(QBERT_R, QBERT_G, QBERT_B, 1.0f);
}

cQubert::cQubert(cPlayState* ps, cQube* q)
       : _spline(0), _playState(ps), _qube(q), m_state(IDLE),
         DEATH_COOLDOWN(1000), JUMP_TIME(500)
{
    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();
    if (_qube->activate())
        ps->ReportQubeActivation();
    _color = Color(QBERT_R, QBERT_G, QBERT_B, 1.0f);
}

void cQubert::move(int i, int k)
{
    if (m_state == CURSING || m_state == DEAD || m_state == JUMPING || m_state == JUMPING_TO_DEATH)
        return;

    cout << _qube->getI() + i << ", " << _qube->getK() + k << endl;

    //map<pair<int, int>, vector<ENTITY::cQube*>*>::iterator it;

    cQube* nQ = _playState->GetQubeAt(_qube->getI() + i, _qube->getK() + k);

    if (nQ == 0) //death!
    {
        cout << "death: Qubert just fell into the abyss!" << endl;
        _playState->ReportQubertDeath();
        _qube = _playState->GetDefaultQube();
        _x = _qube->getX();
        _y = _qube->getY();
        _z = _qube->getZ();
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
    Vec3f p0p(p1_p0.x, 100, p1_p0.z);
    Vec3f p1p(p1_p0.x, -100, p1_p0.z);

    _nextQube = nQ;

    if (_spline != 0)
        delete _spline;

    using MATH::Spline;
    _spline = new Spline(p0, p1, p0p, p1p);
    m_state = JUMPING;
    m_tickAtJumpGather = -1;

    //_x = _qube->getX();
    //_y = _qube->getY();
    //_z = _qube->getZ();
}

void cQubert::handleCollision(float ticks)
{
    m_state = CURSING;
    m_tickAtDeath = (int) ticks;
}

void cQubert::update(CORE::cGame* game, float ticks)
{
    if (m_state == CURSING && (int) ticks - m_tickAtDeath >= DEATH_COOLDOWN)
    {
        //revive
        cout << "revived!" << endl;
        _playState->ReportQubertDeath();
        _playState->Restart();
        _qube = _playState->GetDefaultQube();
        _x = _qube->getX();
        _y = _qube->getY();
        _z = _qube->getZ();
        m_state = IDLE;
    }
    else if (m_state == JUMPING)
    {
        if (m_tickAtJumpGather < 0)
            m_tickAtJumpGather = ticks;

        float u = (ticks - m_tickAtJumpGather) / JUMP_TIME;
        if (u >= 1)
        {
            _qube = _nextQube;

            if (_qube->activate())
                _playState->ReportQubeActivation();

            _x = _qube->getX();
            _y = _qube->getY();
            _z = _qube->getZ();

            m_state = IDLE;
            return;
        }

        using MATH::Vec3f;
        Vec3f pos = _spline->getPosHermite(u);

        _x = pos.x;
        _y = pos.y;
        _z = pos.z;
    }
}

void cQubert::render(float ticks)
{
    //cout << "called" << endl;
    //cout << percent_tick << endl;
    glPushMatrix();
    glTranslatef(_x, _y+Y_OFFSET, _z);

    //draw curses
    if (m_state == CURSING)
    {
        glPushMatrix();             //for hierarchical transformations
        glRotatef(45.0, 0,1,0);
        glRotatef(-30.0, 0,0,1);

        if (p_expletives == 0)
            p_expletives = new cTexture("art/expletive.png");
        p_expletives->RegisterGL();

        cTextureRegion scrn1 = cTextureRegion(*p_expletives);
        glBindTexture(GL_TEXTURE_2D, scrn1.GetID());

        float u   = scrn1.GetU();
        float v   = scrn1.GetV();
        float u2  = scrn1.GetU2();
        float v2  = scrn1.GetV2();

        float Z_OFFSET = 5.0f;

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(u2, v);
        glVertex3f(-10.0f, SPEECH_H/2+Y_OFFSET/1.5, SPEECH_W/2+Z_OFFSET);          // Top Right Of The Quad (Front)

        glTexCoord2f(u, v);
        glVertex3f(-10.0f, SPEECH_H/2+Y_OFFSET/1.5, -SPEECH_W/2+Z_OFFSET);         // Top Left Of The Quad (Front)

        glTexCoord2f(u, v2);
        glVertex3f(-10.0f, -SPEECH_H/2+Y_OFFSET/1.5,-SPEECH_W/2+Z_OFFSET);        // Bottom Left Of The Quad (Front)

        glTexCoord2f(u2, v2);
        glVertex3f(-10.0f, -SPEECH_H/2+Y_OFFSET/1.5, SPEECH_W/2+Z_OFFSET);         // Bottom Right Of The Quad (Front)

        glEnd();

        glBindTexture(GL_TEXTURE_2D, NULL);
        glPopMatrix();
    }

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
