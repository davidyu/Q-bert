#ifndef CQUBERT_H
#define CQUBERT_H

#include <SDL2/SDL_opengl.h>
#include "Color.hpp"
#include "ENTITY_cEntity.hpp"
#include "ENTITY_cQube.hpp"
#include "QBRT_cPlayState.hpp"

class cPlayState;

namespace ENTITY
{
    class cQubert: public cEntity
    {
        public:
            cQubert(cPlayState* ps, Color c); //make playstate singleton?
            cQubert(cPlayState* ps, cQube* q, Color c);

            virtual void render(float percent_tick);
            virtual void update(CORE::cGame* game, float delta);

            void move(int i, int k);

        private:
            float _x,   //will be used for animation
                  _y,
                  _z;

            cQube*      _qube; //which qube am I standing on?
            cPlayState* _playState;

            Color  _color;

    };
}

#endif // CQUBERT_H
