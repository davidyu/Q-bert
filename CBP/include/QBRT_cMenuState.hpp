#ifndef QBRT_CMENUSTATE_H
#define QBRT_CMENUSTATE_H

#include "STATE_iGameState.hpp"
#include "GFX_cTexture.hpp"

namespace CORE
{
    class cGame;
    class Input;
}

class cMenuState : public STATE::iGameState
{
    public:
        cMenuState();
        virtual ~cMenuState();

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
        GFX::cTexture* p_goScreen1;
        GFX::cTexture* p_goScreen2;
        int lastSwappedTick;

};

#endif //QBRT_cMenuState_H
