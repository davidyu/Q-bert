#ifndef CREDBALL_H
#define CREDBALL_H

#include <SDL2/SDL_opengl.h>
#include "Color.hpp"
#include "ENTITY_cEntity.hpp"
#include "ENTITY_cQube.hpp"
#include "QBRT_cPlayState.hpp"

class cPlayState;

namespace ENTITY
{
    class cRedball: public cEntity
    {
        public:
            cRedball(cPlayState* ps, cQube* q, int startTick);

            virtual void render(float ticks);
            virtual void update(CORE::cGame* game, float ticks);
        private:
            //const int _fps;

            int       _ticksSinceExecuteStrategy;
            const int _executeStrategyThresh;
            int _state;

            cQube*      _qube;
            cPlayState* _playState;

            Color  _color;

            void move(int i, int k); //nobody can control me!
    };
}

#endif
