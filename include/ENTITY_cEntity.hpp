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
            virtual void render(float percent_tick) = 0;
            virtual void update(CORE::cGame* game, float delta) = 0;

    };
}

#endif CENTITY_H
