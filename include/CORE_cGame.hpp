#ifndef CGAME_H
#define CGAME_H

#include "SDL2/SDL.h"
#include "CORE_iApplication.hpp"
#include "CORE_cSDLState.hpp"
#include "CORE_Input.hpp"
#include "CORE_cTimer.hpp"
#include "STATE_cGameStateManager.hpp"
#include "cGenericFactory.hpp"

namespace CORE
{


    class cGame : public iApplication
    {
    public:
                                    cGame();
        virtual                     ~cGame();
        /*temp*/ static cGame*      Create() { return new cGame; }
        bool                        Initialise();
        bool                        Terminate();
        void                        MainLoop();
        void                        EndGame();

        CORE::Input&                GetInput();
        STATE::cGameStateManager&   GetStateManager();

        inline SDL_Renderer*        GetRenderer() const{ return m_sdl_state->renderer; }

    protected:
        bool m_running;
        STATE::cGameStateManager    m_state_manager;
        CORE::Input                 m_input;
        CORE::cTimer                m_timer;
        cGenericFactory<STATE::iGameState> state_factory; // FIXME:Should be declared elsewhere


        cSDLState*                  m_sdl_state;

    };

}

#endif // CGAME_H
