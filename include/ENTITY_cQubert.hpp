#ifndef CQUBERT_H
#define CQUBERT_H

#include <SDL2/SDL_opengl.h>
#include "Color.hpp"
#include "ENTITY_cEntity.hpp"
#include "ENTITY_cQube.hpp"
#include "QBRT_cPlayState.hpp"
#include "MATH_Spline.hpp"

class cPlayState;

namespace ENTITY
{
    class cQubert: public cEntity
    {
        public:
            cQubert(cPlayState* ps); //make playstate singleton?
            cQubert(cPlayState* ps, cQube* q);

            virtual void render(float ticks);
            virtual void update(CORE::cGame* game, float ticks);

            void move(int i, int k);
            void handleCollision(float ticks);

            cQube* getQube() { return _qube; } ;

        private:
            cQube*      _qube; //which qube am I standing on?
            cPlayState* _playState;

            const int DEATH_COOLDOWN;


            int m_state;
            int m_tickAtDeath;

            Color  _color;

    };
}

#endif // CQUBERT_H
