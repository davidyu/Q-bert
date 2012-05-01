#ifndef QBRT_CPAUSESTATE_H
#define QBRT_CPAUSESTATE_H

#include "STATE_iGameState.hpp"
#include "GFX_cTexture.hpp"
#include "QBRT_cPlayState.hpp"

class cPlayState;

namespace CORE
{
    class cGame;
    class Input;
}

class cPauseState : public STATE::iGameState
{
    public:
        cPauseState();
        cPauseState(cPlayState* ps);
        virtual ~cPauseState();

        static STATE::iGameState* CreateInstance();
        virtual STATE::iGameState* Clone();

        bool OnEnter();
        bool OnExit();
        void Pause();
        void Resume();

        void Render(CORE::cGame* game, float delta);
        void Update(CORE::cGame* game, float percent_ticks);
    private:
        bool swap;
        GFX::cTexture* p_pause;
        int lastSwappedTick;
        cPlayState* _playState;
        float xrot;
        float yrot;
        const float MOVE_EPSILON;
};

#endif //QBRT_cPauseState_H
