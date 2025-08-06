#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <cmath>
#include <iomanip>

class shapes
{
    public:
        virtual void setPastelColour()=0;
        virtual void setOriginalColour()=0;
        virtual void select()=0;
        virtual void deselect()=0;
        virtual void scaleUp()=0;
        virtual void scaleDown()=0;
        virtual void calcMidPoint(float* coordinates)=0;
        virtual void rotateLeft()=0;
        virtual void rotateRight()=0;
};

class triangle: public shapes
{
    public:
        float vertex[9];
        float col[9];
        bool selected;
        triangle();
        void setPastelColour();
        void setOriginalColour();
        void setColour(std::string colour);
        void select();
        void deselect();
        void move(std::string dir,float d);
        void scaleUp();
        void scaleDown();
        void calcMidPoint(float* coordinates);
        void rotateLeft();
        void rotateRight();

};

class square: public shapes
{
    public:
        float tri1[9];
        float tri2[9];
        bool selected;
        float col[18];
        square();
        void setPastelColour();
        void setOriginalColour();
        void select();
        void deselect();
        void move(std::string dir);
        void scaleUp();
        void scaleDown();
        void calcMidPoint(float* coordinates);
        void rotateLeft();
        void rotateRight();
};

class lowCircle: public shapes //red
{
    public:
        float vertices[30]; //3*10 = 10 vertices
        bool selected;
        float col[30];
        float rad;
        lowCircle();
        void setRadius(float rad);
        void setMidPoint(float* a);
        void setPastelColour();
        void setOriginalColour();
        void setColour(std::string colour);
        void select();
        void deselect();
        void move(std::string dir,float d);
        void scaleUp();
        void scaleDown();
        void calcMidPoint(float* coordinates);
        void rotateLeft();
        void rotateRight();


};


class highCircle: public shapes //orange
{
    public:
        float vertices[180]; //3*60 = 180 vertices
        bool selected;
        float col[180];
        highCircle();
        void setPastelColour();
        void setOriginalColour();
        void select();
        void deselect();
        void move(std::string dir);
        void scaleUp();
        void scaleDown();
        void calcMidPoint(float* coordinates);
        void rotateLeft();
        void rotateRight();


};


class rectangle: shapes
{
    public:
    bool selected;
        float tri1[9];
        float tri2[9];
        float col[24];
        rectangle();
        void setPastelColour();
        void setOriginalColour();
        void setColour(std::string colour,float a);
        void select();
        void deselect();
        void move(std::string dir,float d=0.1);
        void scaleUp();
        void scaleDown();
        void calcMidPoint(float* coordinates);
        void rotateLeft();
        void rotateRight();
};


#endif