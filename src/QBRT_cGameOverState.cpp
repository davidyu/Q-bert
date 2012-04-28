#include "QBRT_cGameOverState.hpp"
#include <iostream>

cGameOverState::cGameOverState() {
    std::cout << "created";
}
cGameOverState::~cGameOverState() {}

STATE::iGameState* cGameOverState::CreateInstance()
{
    return new cGameOverState;
}

STATE::iGameState* cGameOverState::Clone()
{
    return new cGameOverState;
}

void cGameOverState::Pause()
{}

void cGameOverState::Resume()
{}

bool cGameOverState::OnEnter()
{

}

bool cGameOverState::OnExit()
{

}

void cGameOverState::Update(CORE::cGame* game, float delta)
{
    std::cout << "haha";
}

void cGameOverState::Render(CORE::cGame* game, float percent_ticks)
{
    std::cout << "huh?";
}
