#ifndef CQUBERT_H
#define CQUBERT_H

#include <SDL2/SDL_opengl.h>
#include "Color.hpp"
#include "ENTITY_cEntity.hpp"
#include "ENTITY_cQube.hpp"

namespace ENTITY
{
    class cQubert: public cEntity
    {
        public:
            cQubert(Color c);
            cQubert(cQube* q, Color c);

            virtual void render(float percent_tick);
            virtual void update(CORE::cGame* game, float delta);

        private:
            float _x,   //will be used for animation
                  _y,
                  _z;

            cQube* _qube; //which qube am I standing on?

            Color  _color;
    };
}

#endif CQUBERT_H
