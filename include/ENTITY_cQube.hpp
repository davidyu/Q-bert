#ifndef CQUBE_H
#define CQUBE_H

#include <vector>
typedef struct Color
{
    float r;
    float g;
    float b;
    float a;
} Color;

namespace ENTITY
{
    class cQube
    {
        public:
                        cQube(int x, int y, int z, int w, int l, int h, Color top, Color faces);
    };
}

#endif CQUBE_H
