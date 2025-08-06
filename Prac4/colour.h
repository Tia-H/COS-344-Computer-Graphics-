#ifndef COLOURS_H
#define COLOURS_H

#include <iostream>
#include <cmath>
#include <iomanip>

class colour
{
    public:
    float col[3];
    float a[1];
        colour()
        {
            col[0]=0;col[1]=0;col[2]=0;
            a[0]=0;
        };
        void setRed()
        {
            col[0]=1;col[1]=0.01;col[2]=0.01;
        };
        void setOrange()
        {
            col[0]=1;col[1]=0.5;col[2]=0.01;
        };
        void setDarkOrange()
        {
            col[0]=0.9;col[1]=0.4;col[2]=0.01;
        };
        void setYellow()
        {
            col[0]=1;col[1]=1;col[2]=0.01;
        };
        void setGreen()
        {
            col[0]=0.01;col[1]=1;col[2]=0.01;
        };
        void setBlue()
        {
            col[0]=0.01;col[1]=0.01;col[2]=1;
        };
        void setTeal()
        {
            col[0]=0.01;col[1]=1;col[2]=1;
        };
        void setPurple()
        {
            col[0]=0.5;col[1]=0.01;col[2]=1;
        };
        void setPink()
        {
            col[0]=1;col[1]=0.01;col[2]=1;
        };
        void setDarkGrey()
        {
            col[0]=0.3;col[1]=0.3;col[2]=0.3;
        };
        void setLightGrey()
        {
            col[0]=0.8;col[1]=0.8;col[2]=0.8;
        };
        void setGrey()
        {
            col[0]=0.5;col[1]=0.5;col[2]=0.5;
        };
        void setWhite()
        {
            col[0]=1;col[1]=1;col[2]=1;
        };
        void setBlack()
        {
            col[0]=0.001;col[1]=0.001;col[2]=0.001;
        };
        void setTransparency(float num)
        {
            a[0] = num;
        }
};

#endif

