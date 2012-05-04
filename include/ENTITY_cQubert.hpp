#ifndef CQUBERT_H
#define CQUBERT_H

#include <SDL2/SDL_opengl.h>
#include <vector>

#include "Color.hpp"
#include "ENTITY_cEntity.hpp"
#include "ENTITY_cQube.hpp"
#include "QBRT_cPlayState.hpp"
#include "MATH_Spline.hpp"
#include "MATH_Vec3.hpp"

class cPlayState;

using std::vector;

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
            cQube*      _nextQube;
            cPlayState* _playState;
            MATH::Spline* _spline;

            vector<MATH::Vec3f> m_qubert_vertices;
            vector<MATH::Vec3f> m_qubert_normals;
            vector<GLushort>    m_qubert_elements;

            const int DEATH_COOLDOWN;
            const int JUMP_TIME;
            const int JUMP_TIME_EXTENDED;

            int m_state;
            int m_tickAtDeath;

            int m_tickAtJumpGather;

            Color  _color;
    };
}

#endif // CQUBERT_H
