#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <iostream>
#include <cmath>
#include <iomanip>

#include "shapes3D.h"

class aircraft
{
    public:
        aircraft();
};

class wing
{
    public:
        float vertices[(6*18)+(2*204) ];
        int vSize;
        float colours[(6*18)+(2*204) ];
        int cSize;

        cuboid bigWing;
        cylinder sideWing1;
        cylinder sideWing2;
        wing();
        void updateVertices();
        void rotateLeftX(float* mid);
        void rotateRightX(float* mid);
        void rotateLeftY(float* mid);
        void rotateRightY(float* mid);
        void rotateLeftZ(float* mid);
        void rotateRightZ(float* mid);
        void move(std::string d);
};

class body
{
    public:
        float speed;
        float timeInterval;
        float vertices[((30 + (10*9))) + (15*108) +(3*204) +(6*72) +(4*108)];
        int vSize;
        float colours[((30 + (10*9))) +(15*108)+(3*204) +(6*72) +(4*108)];
        int cSize;

        cone planeTail;
        cuboid tailPart1;
        cuboid tailPart2;
        cuboid tailPart3;
        cuboid tailWheelLink;
        cylinder tailWheel;
        triangularPrism leftTail1;
        triangularPrism rightTail1;
        cuboid leftTail2;
        cuboid rightTail2;

        cuboid window;
        triangularPrism leftWindow;
        triangularPrism rightWindow;

        cuboid midBody;
        cuboid nose;

        triangularPrism leftWheelStruct;
        triangularPrism rightWheelStruct;
        cylinder leftWheel;
        cylinder rightWheel;

        cuboid propellerCenter;
        cuboid propeller1;

        cuboid wingStruct1;
        cuboid wingStruct2;
        cuboid wingStruct3;
        cuboid wingStruct4;

        cuboid decor1;
        cuboid decor2;
        cuboid decorR1;
        cuboid decorR2;

        body();
        void updateVertices();
        void calcPlaneMidPoint(float* mid);
        void rotateLeftX(float* mid);
        void rotateRightX(float* mid);
        void rotateLeftY(float* mid);
        void rotateRightY(float* mid);
        void rotateLeftZ(float* mid);
        void rotateRightZ(float* mid);
        void move(std::string d);
        void increaseSpeed();
        void decreaseSpeed();
};

#endif