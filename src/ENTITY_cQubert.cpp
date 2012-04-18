#include "ENTITY_cQubert.hpp"
#include <iostream>

using namespace ENTITY;

const float RADIUS = 5.0f;
const float Y_OFFSET = 3.5f;

cQubert::cQubert(cPlayState* ps, Color c)
       : _playState(ps), _color(c), _qube(ps->GetQubeAt(0,0))
{
    _x = _qube->getX();
    _y = _qube->getY();
    _z = _qube->getZ();
}

cQubert::cQubert(cPlayState* ps, cQube* q, Color c)
       : _playState(ps), _color(c), _qube(q), _x(_qube->getX()), _y(_qube->getY()), _z(_qube->getZ())
{
}

void cQubert::update(CORE::cGame* game, float delta) {}

void cQubert::render(float percent_tick)
{
    glPushMatrix();
    glTranslatef(_x, _y+Y_OFFSET, _z);



}
