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
            cQube(float x, float y, float z, float w, float d, float h, Color up, Color rest);
            cQube(float x, float y, float z, float w, float d, float h, Color up, Color down, Color left, Color right, Color front, Color back);

            virtual void render(float percent_tick);
            virtual void update(CORE::cGame* game, float delta);

            float getX() { return _x; };
            float getY() { return _y; };
            float getZ() { return _z; };

        protected:

        float _x,
              _y,
              _z;

        float _width,
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
