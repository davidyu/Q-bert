#include "ENTITY_cRedball.hpp"
#include <cmath>

using namespace ENTITY;

/* temporary */ #include <iostream>
                using namespace std;

enum State {
    JUMPING,
    IDLE,
    THINKING
};

const float RADIUS = 7.5f;
const float Y_OFFSET = 15.0f;

const int LAT_RESOLUTION = 20;
const int LONG_RESOLUTION = 20;

void cRedball::update(CORE::cGame* game, float ticks)
{
    //don't do anything here; input should be in cPlayState (by design)
    /*
    if (game->GetInput().GetKeyState(SDLK_LEFT))
        game->EndGame();
        */
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
