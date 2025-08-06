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
        float vertices[108];
        float colours[108];

        cuboid();
        void setColour(std::string col);
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
};

class triangularPrism: shapes3D
{
    public:
        int vSize = 72;
        float vertices[72];
        float colours[72];
        triangle front;
        triangle back;
        rectangle r1;
        rectangle r2;
        rectangle r3;

        float degree;
        float width;
        float height;

        triangularPrism();
        void setColour(std::string col);
        void calcMidPoint(float* coordinates);
        void updateVertices();
        void changeVertices();
        void setWidth(float width);
        void setHeight(float h);
        void setMidPoint(float* mid);
        void setDegree(float d);
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
};

class cone: shapes3D
{
    public:
        lowCircle base;
        triangle t1;
        triangle t2;
        triangle t3;
        triangle t4;
        triangle t5;
        triangle t6;
        triangle t7;
        triangle t8;

        cone();
        void setColour(std::string col);
        void setMidPoint(float* coordinates);
        void calcMidPoint(float* coordinates);
        void calcPlaneMidPoint(float* coordinates);
        //rotations
        void rotateLeftX();
        void rotateRightX();
        void rotateLeftY();
        void rotateRightY();
        void rotateLeftZ();
        void rotateRightZ();
        //translations
        void move(std::string d,float diff);
};

class cylinder: shapes3D
{
    public:
        lowCircle top;
        lowCircle bottom;
        rectangle r1;
        rectangle r2;
        rectangle r3;
        rectangle r4;
        rectangle r5;
        rectangle r6;
        rectangle r7;
        rectangle r8;

        float width;
        int vSize=204;
        float vertices[204];
        float colours[204];
        float degree;

        cylinder();
        void setColour(std::string col);
        void updateVertices();
        void changeVertices();
        void calcMidPoint(float* coordinates);
        void setWidth(float width);
        void setRadius(float r);
        void setMidPoint(float* mid);
        void setDegree(float d);
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
        void rotate(float* otherMid,float angle);
};

#endif