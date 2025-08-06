#ifndef SHAPES_3D_H
#define SHAPES_3D_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include "shapes.h"

class shapes3D
{
    public:
        //virtual void move(std::string dir)=0;
        virtual void calcMidPoint(float* coordinates)=0;
};

class cuboid: shapes3D
{
    public:
        rectangle front;
        rectangle back;
        rectangle top;
        rectangle bottom;
        rectangle lSide;
        rectangle rSide;

        float height;
        float width;
        float length;
        float degree;
        int vSize = 108;
        int cSize = 144;
        float vertices[108];
        float colours[144];
        float normals[108];
        float OriginalCol[3];

        //float pos[3];

        cuboid();
        void setRectangles(int r);
        void setColour(std::string col,float a);
        void setHeight(float h);
        void setWidth(float w);
        void setLength(float l);
        void makeTrapezoid();
        void makeLTrapezoid();
        void makeRTrapezoid();
        void changeVertices();
        void updateVertices();
        void updateCol();
        void calcMidPoint(float* coordinates);
        //rotations
        void rotateLeftX(float* mid);
        void rotateRightX(float* mid);
        void rotateLeftY(float* mid);
        void rotateRightY(float* mid);
        void rotateLeftZ(float* mid);
        void rotateRightZ(float* mid);
        //translations
        void move(std::string d);
        void move(std::string d,float n);
        void rotate(float* otherMid);
        void moveUp(cuboid* c);

        void pointLight(cuboid* c); //float* v,float* res,float* norms,
        void calNormal();
        void calFaceNormal(float* p1,float* p2,float* p3,float* res);
};

#endif