#ifndef CREDBALL_H
#define CREDBALL_H

#include "ENTITY_cEntity.hpp"
#include "ENTITY_cQube.hpp"
#include "QBRT_cPlayState.hpp"

class cPlayState;

namespace ENTITY
{
    class cRedball: public cEntity
    {
        public:
            cRedball(cPlayState* ps, cQube* q);

            virtual void render(float ticks);
            virtual void update(CORE::cGame* game, float ticks);
        private:
            const int _fps;

            int _ticksSinceExecute;
            int _state;

            cQube* _qube;
            Color  _color;
    };
}

#endif
