#ifndef SPLINE_H
#define SPLINE_H

#include "MATH_Matrix4x4.hpp"
#include "MATH_Vec3.hpp"
#include "MATH_Vec4.hpp"
#include "MATH_LinearAlgebra.hpp"
#include <cmath>

namespace MATH
{

    class Spline
    {
        public:

            Spline(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3);
            ~Spline() {}
            Vec3f getPosAt(float u);
        private:

            Matrix4x4 m_CatmullRom;

            Vec3f m_p0,
                  m_p1,
                  m_p2,
                  m_p3;

            Vec4f m_x,
                  m_y,
                  m_z;
    };

    inline Spline::Spline(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3)
                  :m_p0(p0), m_p1(p1), m_p2(p2), m_p3(p3)
    {
        m_CatmullRom = Matrix4x4( 0.0f,  2.0f,  0.0f,  0.0f,
                                 -1.0f,  0.0f,  1.0f,  0.0f,
                                  2.0f, -5.0f,  4.0f, -1.0f,
                                 -1.0f,  3.0f, -4.0f,  1.0f );

        m_x = Vec4f(m_p0.x, m_p1.x, m_p2.x, m_p3.x);
        m_y = Vec4f(m_p0.y, m_p1.y, m_p2.y, m_p3.y);
        m_z = Vec4f(m_p0.z, m_p1.z, m_p2.z, m_p3.z);
    }

    inline Vec3f Spline::getPosAt(float u)
    {
        Vec4f uu(0.5, 0.5*u, 0.5*u*u, 0.5*u*u*u);
        Vec4f inter = GetVecMatProd4(uu, m_CatmullRom);
        float x = inter * m_x;
        float y = inter * m_y;
        float z = inter * m_z;

        return Vec3f(x, y, z);
    }
}

#endif //SPLINE_H
