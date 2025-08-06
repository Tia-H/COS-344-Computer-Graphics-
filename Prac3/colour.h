#ifndef COLOURS_H
#define COLOURS_H

#include <iostream>
#include <cmath>
#include <iomanip>

class colour
{
    public:
    float col[3];
        colour()
        {
            col[0]=0;col[1]=0;col[2]=0;
        };
        void setRed()
        {
            col[0]=1;col[1]=0;col[2]=0;
        };
        void setOrange()
        {
            col[0]=1;col[1]=0.5;col[2]=0;
        };
        void setDarkOrange()
        {
            col[0]=0.9;col[1]=0.4;col[2]=0;
        };
        void setYellow()
        {
            col[0]=1;col[1]=1;col[2]=0;
        };
        void setGreen()
        {
            col[0]=0;col[1]=1;col[2]=0;
        };
        void setBlue()
        {
            col[0]=0;col[1]=0;col[2]=1;
        };
        void setTeal()
        {
            col[0]=0;col[1]=1;col[2]=1;
        };
        void setPurple()
        {
            col[0]=0.5;col[1]=0;col[2]=1;
        };
        void setPink()
        {
            col[0]=1;col[1]=0;col[2]=1;
        };
        void setDarkGrey()
        {
            col[0]=0.3;col[1]=0.3;col[2]=0.3;
        };
        void setLightGrey()
        {
            col[0]=0.8;col[1]=0.8;col[2]=0.8;
        };
        void setWhite()
        {
            col[0]=1;col[1]=1;col[2]=1;
        };
        void setBlack()
        {
            col[0]=0;col[1]=0;col[2]=0;
        };
};

#endif

