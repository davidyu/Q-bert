#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <fstream>
#include <sstream>

#include "MATH_Vec3.hpp"

/* temp */ #include <iostream>

using MATH::Vec3f;
using MATH::Vec3;
using namespace std;

/**
 *	A simple .obj loader
 *	\file		GFX_Parser.hpp
 *	\author		Lewen Yu
 *	\date		May 3, 2012
 *  \brief      Clone of code from http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
 */

namespace GFX
{
    inline int LoadObj(const char* filename, vector<Vec3f> &vertices, vector<Vec3f> &normals, vector<GLushort> &elements)
    {
        ifstream in(filename, ios::in);
        if (!in)
        {
            cerr << filename << " does not exist." << endl;
            return -1;
        }

        string line;
        while (getline(in, line))
        {
            if (line.substr(0,2) == "v ")
            {
                istringstream s(line.substr(2));
                Vec3f v;
                s >> v.x >> v.y >> v.z;
                vertices.push_back(v);
            }
            else if (line.substr(0,2) == "f ")
            {
                istringstream s(line.substr(2));
                GLushort a,b,c;
                s >> a >> b >> c;
                a--;
                b--;
                c--;
                elements.push_back(a);
                elements.push_back(b);
                elements.push_back(c);
            }
        }

        normals.resize(vertices.size(), Vec3f(0.0, 0.0, 0.0));
        for (int i = 0; i < elements.size(); i+=3)
        {
            GLushort ia = elements[i];
            GLushort ib = elements[i+1];
            GLushort ic = elements[i+2];

            Vec3f normal = Vec3f::Cross(vertices[ib] - vertices[ia], vertices[ic] - vertices[ia]);
            normals[ia] = normals[ib] = normals[ic] = normal;
        }

        return 0;
    }
}

#endif //PARSER_H
