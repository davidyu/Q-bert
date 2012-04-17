#include "ENTITY_cQube.hpp"
#include <vector>

//comments borrowed from NeHe:http://nehe.gamedev.net/tutorial/3d_shapes/10035/

using namespace ENTITY;

cQube::cQube(int x, int y, int z, int w, int d, int h, Color up, Color rest)
      :_x(x), _y(y), _z(z), _width(w), _depth(d), _height(h), _up(up), _down(rest), _left(rest), _right(rest), _front(rest), _back(rest)
{
}

cQube::cQube(int x, int y, int z, int w, int d, int h, Color up, Color down, Color left, Color right, Color front, Color back)
      :_x(x), _y(y), _z(z), _width(w), _depth(d), _height(h), _up(up), _down(down), _left(left), _right(right), _front(front), _back(back)
{
}

void cQube::render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(_x, _y, _z);

    //up face
    glBegin(GL_QUADS);
    glColor3f(_up.getR(), _up.getG(), _up.getB());
    glVertex3f(_width/2, _height/2, -_depth/2);         // Top Right Of The Quad (Top)
    glVertex3f(-_width/2, _height/2, -_depth/2);        // Top Left Of The Quad (Top)
    glVertex3f(-_width/2, _height/2, _depth/2);         // Bottom Left Of The Quad (Top)
    glVertex3f(_width/2, _height/2, _depth/2);          // Bottom Right Of The Quad (Top)
    glEnd();

    glLoadIdentity();
    glTranslatef(_x, _y, _z);

    //down face
    glBegin(GL_QUADS);
    glColor3f(_down.getR(), _down.getG(), _down.getB());
    glVertex3f(_width/2, -_height/2, _depth/2);         // Top Right Of The Quad (Bottom)
    glVertex3f(-_width/2, -_height/2, _depth/2);        // Top Left Of The Quad (Bottom)
    glVertex3f(-_width/2, -_height/2, -_depth/2);       // Bottom Left Of The Quad (Bottom)
    glVertex3f(_width/2, -_height/2, -_depth/2);        // Bottom Right Of The Quad (Bottom)
    glEnd();

    glLoadIdentity();
    glTranslatef(_x, _y, _z);

    //front face
    glBegin(GL_QUADS);
    glColor3f(_front.getR(), _front.getG(), _front.getB());
    glVertex3f(_width/2, _height/2, _depth/2);          // Top Right Of The Quad (Front)
    glVertex3f(-_width/2, _height/2, _depth/2);         // Top Left Of The Quad (Front)
    glVertex3f(-_width/2, -_height/2, _depth/2);        // Bottom Left Of The Quad (Front)
    glVertex3f(_width/2, -_height/2, _depth/2);         // Bottom Right Of The Quad (Front)
    glEnd();

    glLoadIdentity();
    glTranslatef(_x, _y, _z);

    //back face
    glBegin(GL_QUADS);
    glColor3f(_back.getR(), _back.getG(), _back.getB());
    glVertex3f(_width/2, -_height/2, -_depth/2);        // Bottom Left Of The Quad (Back)
    glVertex3f(-_width/2, -_height/2, -_depth/2);       // Bottom Right Of The Quad (Back)
    glVertex3f(-_width/2, _height/2, -_depth/2);        // Top Right Of The Quad (Back)
    glVertex3f(_width/2, _height/2, -_depth/2);// Top Left Of The Quad (Back)
    glEnd();

    glLoadIdentity();
    glTranslatef(_x, _y, _z);

    //left face
    glBegin(GL_QUADS);
    glColor3f(_left.getR(), _left.getG(), _left.getB());
    glVertex3f(-_width/2, _height/2, _depth/2);// Top Right Of The Quad (Left)
    glVertex3f(-_width/2, _height/2, -_depth/2);// Top Left Of The Quad (Left)
    glVertex3f(-_width/2, -_height/2, -_depth/2);// Bottom Left Of The Quad (Left)
    glVertex3f(-_width/2, -_height/2, _depth/2);// Bottom Right Of The Quad (Left)
    glEnd();

    glLoadIdentity();
    glTranslatef(_x, _y, _z);

    //right face
    glBegin(GL_QUADS);
    glColor3f(_right.getR(), _right.getG(), _right.getB());
    glVertex3f(_width/2, _height/2, -_depth/2);// Top Right Of The Quad (Left)
    glVertex3f(_width/2, _height/2, _depth/2);// Top Left Of The Quad (Left)
    glVertex3f(_width/2, -_height/2, _depth/2);// Bottom Left Of The Quad (Left)
    glVertex3f(_width/2, -_height/2, -_depth/2);// Bottom Right Of The Quad (Left)
    glEnd();

    glPopMatrix();
}
