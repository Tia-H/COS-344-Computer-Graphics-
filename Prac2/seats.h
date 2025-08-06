#ifndef SEATS_H
#define SEATS_H

#include <iostream>
#include <cmath>
#include <iomanip>

class seats
{
    public:
        virtual void setPastelColour()=0;
        virtual void setOriginalColour()=0;
        virtual void select()=0;
        virtual void deselect()=0;
        virtual void move(std::string dir)=0;
        virtual void scaleUp()=0;
        virtual void scaleDown()=0;
        virtual void calcMidPoint(float* coordinates)=0;
        virtual void rotateLeft()=0;
        virtual void rotateRight()=0;
};

class triangleSeat: public seats
{
    public:
        float vertex[9];
        float col[9];
        bool selected;
        triangleSeat();
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

class squareSeat: public seats
{
    public:
        float tri1[9];
        float tri2[9];
        bool selected;
        float col[18];
        squareSeat();
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

class circleSeat: public seats //red
{
    public:
        float vertices[30]; //3*10 = 10 vertices
        bool selected;
        float col[30];
        circleSeat();
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

class highCircleSeat: public seats //yellow
{
    public:
        float vertices[150]; //3*50 = 150 vertices
        bool selected;
        float col[150];
        highCircleSeat();
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

class higherCircleSeat: public seats //orange
{
    public:
        float vertices[180]; //3*60 = 180 vertices
        bool selected;
        float col[180];
        higherCircleSeat();
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

class decor
{
    public:
        virtual void setPastelColour()=0;
        virtual void setOriginalColour()=0;
        virtual void select()=0;
        virtual void deselect()=0;
        virtual void move(std::string dir)=0;
        virtual void scaleUp()=0;
        virtual void scaleDown()=0;
        virtual void calcMidPoint(float* coordinates)=0;
        virtual void rotateLeft()=0;
        virtual void rotateRight()=0;
};

class trianglePlant: public decor
{
    public:
        float vertex[9];
        float col[9];
        bool selected;
        trianglePlant();
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

class circleTable: public decor
{
    public:
        float vertices[24]; //3*8 = 8 vertices
        bool selected;
        float col[24];
        circleTable();
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

class bin: public decor
{
    public:
        float vertices[153]; //3*51 = 51 vertices
        bool selected;
        float col[153];
        bin();
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

class Rectangle
{
    public:
        float tri1[9];
        float tri2[9];
        float col[18];
        Rectangle();
        void move(std::string dir);
        void scaleUp();
        void scaleDown();
        void calcMidPoint(float* coordinates);
};

class Square
{
    public:
        float tri1[9];
        float tri2[9];
        float col[18];
        Square();
        void move(std::string dir);
        void scaleUp();
        void scaleDown();
        void calcMidPoint(float* coordinates);
};


#endif