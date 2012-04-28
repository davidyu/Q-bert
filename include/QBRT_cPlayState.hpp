#ifndef QBRT_CPLAYSTATE_H
#define QBRT_CPLAYSTATE_H

#include <vector>
#include <map>
#include <utility>
#include "STATE_iGameState.hpp"
#include "ENTITY_cQube.hpp"
#include "ENTITY_cQubert.hpp"
#include "ENTITY_cRedball.hpp"
//
/*temp*/#include <iostream>

namespace CORE
{
    class cGame;
    class Input;
}

namespace ENTITY
{
    class cQubert; //why do I have to do this? cQube doesn't need this...
    class cEntity;
}

//static STATE::iGameState* CreateInstance() {}

using std::vector;
using std::map;
using std::pair;

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

        void Update(CORE::cGame* game, float ticks);

        void Render(CORE::cGame* game, float ticks);

        void HandleInput();

        void Remove(ENTITY::cEntity* e); //removes entity

        ENTITY::cQube* GetQubeAt(int i, int j);
        ENTITY::cQube* GetDefaultQube() { return _defaultQube; };

    private:
        map<pair<int, int>, vector<ENTITY::cQube*>*> qubes;
        vector<ENTITY::cEntity*> entities;
        ENTITY::cQubert*  _qubert;
        ENTITY::cQube*    _defaultQube;

        const int _addEnemyThresh;
        int       _lastEnemyGenTick;

        void loadLevel();
        void addQubert();
        void addEnemy(float now);

    protected:

};

#endif // QBRT_CPLAYSTATE_H
