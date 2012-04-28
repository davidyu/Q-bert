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
            cQube(float x, float y, float z, float w, float d, float h, int i, int j, int k,
                  Color up, Color activated, Color rest);
            cQube(float x, float y, float z, float w, float d, float h, int i, int j, int k,
                  Color up, Color activated, Color down, Color left, Color right, Color front, Color back);

            virtual void render(float ticks);
            virtual void update(CORE::cGame* game, float ticks);

            float getX() { return _x; };
            float getY() { return _y; };
            float getZ() { return _z; };

            int   getI() { return _i; };
            int   getJ() { return _j; };
            int   getK() { return _k; };

            void activate();

        protected:

        float _x,
              _y,
              _z;

        int   _i, //indices in map - corresponds to x
              _j, // corresponds to z
              _k; // corresponds to y

        float _width,
              _depth,
              _height;

        Color _up,
              _activated,
              _down,
              _left,
              _right,
              _front,
              _back;
    };
}

#endif // CQUBE_H
