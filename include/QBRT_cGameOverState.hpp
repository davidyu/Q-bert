#ifndef QBRT_CGAMEOVERSTATE_H
#define QBRT_CGAMEOVERSTATE_H

#include "STATE_iGameState.hpp"

namespace CORE
{
    class cGame;
    class Input;
}

class cGameOverState : public STATE::iGameState
{
    public:
        cGameOverState();
        virtual ~cGameOverState();

        static STATE::iGameState* CreateInstance();
        virtual STATE::iGameState* Clone();

        bool OnEnter();
        bool OnExit();
        void Pause();
        void Resume();

        void Render(CORE::cGame* game, float delta);
        void Update(CORE::cGame* game, float percent_ticks);
};

#endif //QBRT_CGAMEOVERSTATE_H
