#ifndef CREDBALL_H
#define CREDBALL_H

#include <SDL2/SDL_opengl.h>
#include "Color.hpp"
#include "ENTITY_cEntity.hpp"
#include "ENTITY_cQube.hpp"
#include "QBRT_cPlayState.hpp"
#include "MATH_Spline.hpp"

class cPlayState;

namespace ENTITY
{
    class cRedball: public cEntity
    {
        public:
            cRedball(cPlayState* ps, cQube* q, int startTick);

            virtual void render(float ticks);
            virtual void update(CORE::cGame* game, float ticks);

            cQube* getQube() { return _qube; };
        private:
            //const int _fps;

            int       _ticksSinceExecuteStrategy;
            int       m_tickAtJumpGather;
            const int _executeStrategyThresh;
            const int JUMP_TIME;
            const int JUMP_TIME_EXTENDED;
            int       _state;

            cQube*      _qube;
            cQube*      _nextQube;
            cPlayState* _playState;

            MATH::Spline* _spline;

            Color  _color;

            const float RADIUS;
            const float Y_OFFSET;

            const int LAT_RESOLUTION;
            const int LONG_RESOLUTION;

            void move(int i, int k); //nobody can control me!
    };
}

#endif
