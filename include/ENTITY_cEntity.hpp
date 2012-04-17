#ifndef CENTITY_H
#define CENTITY_H

namespace ENTITY
{
    class cEntity
    {
        public:
            cEntity();
            virtual ~cEntity();
            virtual void render() = 0;

    };
}

#endif CENTITY_H
