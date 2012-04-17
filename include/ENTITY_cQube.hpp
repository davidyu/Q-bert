#ifndef CQUBE_H
#define CQUBE_H

#include <vector>
#include <SDL2/SDL_opengl.h>
#include "Color.hpp"
#include "ENTITY_cEntity.hpp"

namespace ENTITY
{
    class cQube: public cEntity
    {
        public:
            cQube(int x, int y, int z, int w, int d, int h, Color up, Color rest);
            cQube(int x, int y, int z, int w, int d, int h, Color up, Color down, Color left, Color right, Color front, Color back);

            virtual void render();

        protected:

        int _x,
            _y,
            _z;

        int _width,
            _depth,
            _height;

        Color _up,
              _down,
              _left,
              _right,
              _front,
              _back;
    };
}

#endif CQUBE_H
