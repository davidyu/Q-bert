#include "ENTITY_cQubert.hpp"
#include <iostream>

using namespace ENTITY;

cQubert::cQubert(Color c)
       : _color(c)
{
}

cQubert::cQubert(cQube* q, Color c)
       : _color(c), _qube(q)
{
}

void cQubert::update(CORE::cGame* game, float delta) {}

void cQubert::render(float percent_tick) {}
