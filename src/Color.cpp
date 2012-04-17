#include "Color.hpp"

Color::Color(float r, float g, float b, float a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

Color::Color(const Color& copy)
:_r(copy.getR()), _g(copy.getG()), _b(copy.getB()), _a(copy.getA())
{

}

Color::~Color()
{
    //dtor
}
