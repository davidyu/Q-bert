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

bool Color::operator==(const Color &other) const {
    if (_r == other.getR() && _g == other.getG() && _b == other.getB())
        return true;
    return false;
}
