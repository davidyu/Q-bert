#ifndef CENTITY_H
#define CENTITY_H

namespace CORE
{
    class cGame;
    class Input;
}

namespace ENTITY
{
    class cEntity
    {
        public:
            cEntity();
            virtual ~cEntity();
            virtual void render(float ticks) = 0;
            virtual void update(CORE::cGame* game, float ticks) = 0;
        protected:
            float _x,   //for animation
                  _y,
                  _z;
    };
}

#endif
