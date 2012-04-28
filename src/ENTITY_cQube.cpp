#include "ENTITY_cQube.hpp"
#include <vector>
#include <iostream>

//cube code and comments heavily based on (and borrowed) from
// NeHe: http://nehe.gamedev.net/tutorial/3d_shapes/10035/

using namespace ENTITY;

cQube::cQube(float x, float y, float z, float w, float d, float h, int i, int j, int k,
             Color up, Color activated, Color rest)
      :_x(x), _y(y), _z(z), _i(i), _j(j), _k(k), _width(w), _depth(d), _height(h),
       _up(up), _activated(activated), _down(rest), _left(rest), _right(rest), _front(rest), _back(rest)
{
}

cQube::cQube(float x, float y, float z, float w, float d, float h, int i, int j, int k,
             Color up, Color activated, Color down, Color left, Color right, Color front, Color back)
      :_x(x), _y(y), _z(z), _i(i),  _j(j), _k(k), _width(w), _depth(d),  _height(h),
      _up(up), _activated(activated), _down(down), _left(left), _right(right), _front(front), _back(back)
{
}

void cQube::update(CORE::cGame* game, float ticks) {}

void cQube::activate()
{
    _up = _activated;
}

void cQube::render(float ticks)
{
    glPushMatrix();
    //glLoadIdentity(); - this makes everything flat
    glTranslatef(_x, _y, _z);

    //up face
    glBegin(GL_QUADS);
    glColor3f(_up.getR(), _up.getG(), _up.getB());
    glVertex3f(_width/2, _height/2, -_depth/2);         // Top Right Of The Quad (Top)
    glVertex3f(-_width/2, _height/2, -_depth/2);        // Top Left Of The Quad (Top)
    glVertex3f(-_width/2, _height/2, _depth/2);         // Bottom Left Of The Quad (Top)
    glVertex3f(_width/2, _height/2, _depth/2);          // Bottom Right Of The Quad (Top)

    //down face
    glColor3f(_down.getR(), _down.getG(), _down.getB());
    glVertex3f(_width/2, -_height/2, _depth/2);         // Top Right Of The Quad (Bottom)
    glVertex3f(-_width/2, -_height/2, _depth/2);        // Top Left Of The Quad (Bottom)
    glVertex3f(-_width/2, -_height/2, -_depth/2);       // Bottom Left Of The Quad (Bottom)
    glVertex3f(_width/2, -_height/2, -_depth/2);        // Bottom Right Of The Quad (Bottom)

    //front face
    glColor3f(_front.getR(), _front.getG(), _front.getB());
    glVertex3f(_width/2, _height/2, _depth/2);          // Top Right Of The Quad (Front)
    glVertex3f(-_width/2, _height/2, _depth/2);         // Top Left Of The Quad (Front)
    glVertex3f(-_width/2, -_height/2, _depth/2);        // Bottom Left Of The Quad (Front)
    glVertex3f(_width/2, -_height/2, _depth/2);         // Bottom Right Of The Quad (Front)

    //back face
    glColor3f(_back.getR(), _back.getG(), _back.getB());
    glVertex3f(_width/2, -_height/2, -_depth/2);        // Bottom Left Of The Quad (Back)
    glVertex3f(-_width/2, -_height/2, -_depth/2);       // Bottom Right Of The Quad (Back)
    glVertex3f(-_width/2, _height/2, -_depth/2);        // Top Right Of The Quad (Back)
    glVertex3f(_width/2, _height/2, -_depth/2);         // Top Left Of The Quad (Back)

    //left face
    glColor3f(_left.getR(), _left.getG(), _left.getB());
    glVertex3f(-_width/2, _height/2, _depth/2);         // Top Right Of The Quad (Left)
    glVertex3f(-_width/2, _height/2, -_depth/2);        // Top Left Of The Quad (Left)
    glVertex3f(-_width/2, -_height/2, -_depth/2);       // Bottom Left Of The Quad (Left)
    glVertex3f(-_width/2, -_height/2, _depth/2);// Bottom Right Of The Quad (Left)

    //right face
    glColor3f(_right.getR(), _right.getG(), _right.getB());
    glVertex3f(_width/2, _height/2, -_depth/2);// Top Right Of The Quad (Left)
    glVertex3f(_width/2, _height/2, _depth/2);// Top Left Of The Quad (Left)
    glVertex3f(_width/2, -_height/2, _depth/2);// Bottom Left Of The Quad (Left)
    glVertex3f(_width/2, -_height/2, -_depth/2);// Bottom Right Of The Quad (Left)
    glEnd();

    glPopMatrix();
}
