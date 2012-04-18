#ifndef CQUBERT_H
#define CQUBERT_H

#include "ENTITY_cEntity.hpp"
#include "Color.hpp"
#include "ENTITY_cQube.hpp"
#include <SDL2/SDL_opengl.h>

namespace ENTITY
{
    class cQubert: public cEntity
    {
        public:
            cQubert(Color c);
            cQubert(cQube* q, Color c);

            virtual void render(float percent_tick);

        private:

            float _x,   //will be used for animation
                  _y,
                  _z;

            cQube* qube; //which qube am I standing on?
    };
}

#endif
