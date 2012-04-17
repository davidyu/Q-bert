#ifndef DEMO_CPLAYSTATE_H
#define DEMO_CPLAYSTATE_H

#include <vector>
#include "STATE_iGameState.hpp"
#include "ENTITY_cQube.hpp"
//
/*temp*/#include <iostream>

namespace CORE
{
    class cGame;
    class Input;
}

//static STATE::iGameState* CreateInstance() {}

using std::vector;

class cPlayState : public STATE::iGameState
{
    public:
        cPlayState();
        virtual ~cPlayState();

        static STATE::iGameState* CreateInstance();
        virtual STATE::iGameState* Clone(); // Ideally this function should return a copy, not a blank instance

        bool OnEnter();
        bool OnExit();
        void Pause();
        void Resume();

        void Update(CORE::cGame* game, float delta);

        void Render(CORE::cGame* game, float percent_tick);

        void HandleInput();
    private:
        vector<ENTITY::cEntity*> entities;
        void loadLevel();
    protected:

};

#endif // DEMO_CPLAYSTATE_H
