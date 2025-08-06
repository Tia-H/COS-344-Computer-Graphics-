#include "colour.h"

triangle::triangle()
{
    vertex[0] = -0.1;vertex[1] =0.1;vertex[2]=0;
    vertex[3] = 0;vertex[4] =0.1;vertex[5]=0;
    vertex[6] = -0.1;vertex[7] =0.2;vertex[8]=0;
    selected = false;
    setOriginalColour();
}
void triangle::setPastelColour()
{
    col[0] = 0.5;col[1] = 0.5;col[2] = 1;
    col[3] = 0.5;col[4] = 0.5;col[5] = 1;
    col[6] = 0.5;col[7] = 0.5;col[8] = 1;
}
void triangle::setOriginalColour()
{
    col[0] = 0.5;col[1] = 0;col[2] = 1;
    col[3] = 0.5;col[4] = 0;col[5] = 1;
    col[6] = 0.5;col[7] = 0;col[8] = 1;
}
void triangle::setColour(std::string c)
{
    colour currColour;
    if (c=="red")
    {
        currColour.setRed();
        for (int i=0;i<9;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="pink")
    {
        currColour.setPink();
        for (int i=0;i<9;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="blue")
    {
        currColour.setBlue();
        for (int i=0;i<9;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="yellow")
    {
        currColour.setYellow();
        for (int i=0;i<9;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="orange")
    {
        currColour.setOrange();
        for (int i=0;i<9;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="darkOrange")
    {
        currColour.setDarkOrange();
        for (int i=0;i<9;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
}
void triangle::select()
{
    selected=true;
    setPastelColour();
}
void triangle::deselect()
{
    selected = false;
    setOriginalColour();
}

void triangle::move(std::string direction,float diff)
{
    float d = diff;
        if (direction=="up")
        {
            //if (vertex[1]+d<0.9 && vertex[4]+d<0.9 && vertex[7]+d<0.9)
            {
                vertex[1] += d;
                vertex[4] += d;
                vertex[7] += d;
            }
        }else if (direction=="down")
        {
            //if (vertex[1]-d>-0.9 && vertex[4]-d>-0.9 && vertex[7]-d>-0.9)
            {
                vertex[1] -= d;
                vertex[4] -= d;
                vertex[7] -= d;
            }
        }else if (direction=="right")
        {
            //if (vertex[0]+d<0.9 && vertex[3]+d<0.9 && vertex[6]+d<0.9)
            {
                vertex[0] += d;
                vertex[3] += d;
                vertex[6] += d;
            }
        }else if (direction=="left")
        {
            //if (vertex[0]-d>-0.9 && vertex[3]-d>-0.9 && vertex[6]-d>-0.9)
            {
                vertex[0] -= d;
                vertex[3] -= d;
                vertex[6] -= d;
            }
        }else if (direction=="incZ")
        {
            vertex[2] += d;
            vertex[5] += d;
            vertex[8] += d;
        }
        else if (direction=="decZ")
        {
            vertex[2] -= d;
                vertex[5] -= d;
                vertex[8] -= d;
        }
}

void triangle::scaleUp()
{
    //if (vertex[1]+d<0.9 && vertex[4]+d<0.9 && vertex[7]+d<0.9)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<8;i+=3)
        {
            if (i!=2 || i!=5)
            {
                vertex[i] -= coords[x];
                vertex[i+1] -= coords[y];

                vertex[i] *= s;
                vertex[i+1] *= s;

                vertex[i] += coords[x];
                vertex[i+1] += coords[y];
            }
        }

    }
}
void triangle::scaleDown()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<8;i+=3)
        {
            if (i!=2 || i!=5)
            {
                vertex[i] -= coords[x];
                vertex[i+1] -= coords[y];

                vertex[i] *= s;
                vertex[i+1] *= s;

                vertex[i] += coords[x];
                vertex[i+1] += coords[y];
            }
        }
    }
}

void triangle::calcMidPoint(float* coordinates)
{
    int x=0;int y=1;
    coordinates[x] = 0; //[0]=x,[1]=y
    coordinates[y] = 0;
    for (int i=0;i<3;i++)
    {
        coordinates[x] += vertex[i*3]  ;
        coordinates[y] += vertex[i*3+y]  ;
    }
    coordinates[x] /= 3;
    coordinates[y] /= 3;
}
void triangle::rotateLeft()
{
    float angle=0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);


    for (int i=0; i<9; i+=3)
    {
        vertex[i] -= coords[x];
        vertex[i+1] -= coords[y];
        float numx = vertex[i]*cos(angle) - vertex[i+1]*sin(angle);
        float numy = vertex[i]*sin(angle) + vertex[i+1]*cos(angle);
        vertex[i] = numx +coords[x];
        vertex[i+1] =numy +coords[y];
    }
}
void triangle::rotateRight()
{
    float angle=-0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);
    /*for (int i=0; i<9; i+=2)
    {
        vertex[i] -= coords[x];
        vertex[i+1] -= coords[y];
    }*/


    for (int i=0; i<9; i+=3)
    {
        vertex[i] -= coords[x];
        vertex[i+1] -= coords[y];
        float numx = vertex[i]*cos(angle) - vertex[i+1]*sin(angle);
        float numy = vertex[i]*sin(angle) + vertex[i+1]*cos(angle);
        vertex[i] = numx +coords[x];
        vertex[i+1] =numy +coords[y];
    }
}

square::square()
{
    tri1[0] = -0.1; tri1[1] =0.2;   tri1[2]=0;
    tri1[3] = 0;    tri1[4] =0.2;   tri1[5]=0;
    tri1[6] = -0.1;    tri1[7] =0.1;   tri1[8]=0;

    tri2[0] = 0;    tri2[1] =0.2;   tri2[2]=0;
    tri2[3] = 0;    tri2[4] =0.1;   tri2[5]=0;
    tri2[6] = -0.1;    tri2[7] =0.1;   tri2[8]=0;
    selected = false;
    setOriginalColour();
}

void square::setPastelColour()
{
    for (int i=0;i<18;i++)
    {
        col[i] = 0.35;
    }
    for (int i=2;i<18;i+=3)
    {
        col[i] = 1;
    }
}
void square::setOriginalColour()
{
    col[0] = 0;col[1] = 0;col[2] = 1;
    col[3] = 0;col[4] = 0;col[5] = 1;
    col[6] = 0;col[7] = 0;col[8] = 1;
    col[9] = 0;col[10] = 0;col[11] = 1;
    col[12] = 0;col[13] = 0;col[14] = 1;
    col[15] = 0;col[16] = 0;col[17] = 1;
}
void square::select()
{
    selected=true;
    setPastelColour();
}
void square::deselect()
{
    selected = false;
    setOriginalColour();
}
void square::move(std::string direction)
{
    float d = 0.02;
        if (direction=="up")
        {
            //if (tri1[1]+d<0.9 && tri1[4]+d<0.9 && tri1[7]+d<0.9 && tri2[1]+d<0.9 && tri2[4]+d<0.9 && tri2[7]+d<0.9)
            {
                tri1[1] += d;
                tri1[4] += d;
                tri1[7] += d;
                tri2[1] += d;
                tri2[4] += d;
                tri2[7] += d;
            }
        }else if(direction=="down")
        {
            //if (tri1[1]-d>-0.9 && tri1[4]-d>-0.9 && tri1[7]-d>-0.9 && tri2[1]-d>-0.9 && tri2[4]-d>-0.9 && tri2[7]-d>-0.9)
            {
                tri1[1] -= d;
                tri1[4] -= d;
                tri1[7] -= d;
                tri2[1] -= d;
                tri2[4] -= d;
                tri2[7] -= d;
            }
        }else if (direction=="right")
        {
            //if (tri1[0]+d<0.9 && tri1[3]+d<0.9 && tri1[6]+d<0.9 && tri2[0]+d<0.9 && tri2[3]+d<0.9 && tri2[6]+d<0.9)
            {
                tri1[0] += d;
                tri1[3] += d;
                tri1[6] += d;
                tri2[0] += d;
                tri2[3] += d;
                tri2[6] += d;
            }
        }else if (direction=="left")
        {
            //if (tri1[0]-d>-0.9 && tri1[3]-d>-0.9 && tri1[6]-d>-0.9 && tri2[0]-d>-0.9 && tri2[3]-d>-0.9 && tri2[6]-d>-0.9)
            {
                tri1[0] -= d;
                tri1[3] -= d;
                tri1[6] -= d;
                tri2[0] -= d;
                tri2[3] -= d;
                tri2[6] -= d;
            }
        }
}
void square::scaleUp()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<8;i+=3)
        {
            //if (i!=2 || i!=5)
            {
                tri1[i] -= coords[x];
                tri1[i+1] -= coords[y];
                tri2[i] -= coords[x];
                tri2[i+1] -= coords[y];

                tri1[i] *= s;
                tri1[i+1] *= s;
                tri2[i] *= s;
                tri2[i+1] *= s;

                tri1[i] += coords[x];
                tri1[i+1] += coords[y];
                tri2[i] += coords[x];
                tri2[i+1] += coords[y];
            }
        }
    }
}
void square::scaleDown()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<8;i+=3)
        {
            //if (i!=2 || i!=5)
            {
                tri1[i] -= coords[x];
                tri1[i+1] -= coords[y];
                tri2[i] -= coords[x];
                tri2[i+1] -= coords[y];

                tri1[i] *= s;
                tri1[i+1] *= s;
                tri2[i] *= s;
                tri2[i+1] *= s;

                tri1[i] += coords[x];
                tri1[i+1] += coords[y];
                tri2[i] += coords[x];
                tri2[i+1] += coords[y];
            }
        }
    }
}
void square::calcMidPoint(float* coordinates)
{
    int x=0; int y=1;
    coordinates[x]=0;
    coordinates[y]=0;
    for (int i=0; i<9 ;i+=3)
    {
        coordinates[x] += tri1[i] + tri2[i];
        coordinates[y] += tri1[i+y] + tri2[i+y];
    }
    coordinates[x] /= 6;
    coordinates[y] /= 6;
}
void square::rotateLeft()
{
    float angle=0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<9; i+=3)
    {
        tri1[i] -= coords[x];
        tri1[i+1] -= coords[y];
        tri2[i] -= coords[x];
        tri2[i+1] -= coords[y];

        float numx1 = tri1[i]*cos(angle) - tri1[i+1]*sin(angle);
        float numy1 = tri1[i]*sin(angle) + tri1[i+1]*cos(angle);
        float numx2 = tri2[i]*cos(angle) - tri2[i+1]*sin(angle);
        float numy2 = tri2[i]*sin(angle) + tri2[i+1]*cos(angle);

        tri1[i] = numx1 +coords[x];
        tri1[i+1] =numy1 +coords[y];
        tri2[i] = numx2 +coords[x];
        tri2[i+1] =numy2 +coords[y];
    }
}
void square::rotateRight()
{
    float angle=-0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<9; i+=3)
    {
        tri1[i] -= coords[x];
        tri1[i+1] -= coords[y];
        tri2[i] -= coords[x];
        tri2[i+1] -= coords[y];

        float numx1 = tri1[i]*cos(angle) - tri1[i+1]*sin(angle);
        float numy1 = tri1[i]*sin(angle) + tri1[i+1]*cos(angle);
        float numx2 = tri2[i]*cos(angle) - tri2[i+1]*sin(angle);
        float numy2 = tri2[i]*sin(angle) + tri2[i+1]*cos(angle);

        tri1[i] = numx1 +coords[x];
        tri1[i+1] =numy1 +coords[y];
        tri2[i] = numx2 +coords[x];
        tri2[i+1] =numy2 +coords[y];
    }
}


lowCircle::lowCircle()
{
    rad=0.1;
    vertices[0] = 0; vertices[1]=0; vertices[2] =0; //x,y,z -> center of circle
    
    float p2= 2.0*M_PI;
    for (int i=1; i<10; i++)
    {
        float a = p2*i / 8;
        vertices[3*i]= rad*cos(a);
        vertices[3*i+1]= rad*sin(a);
        vertices[3*i+2]= 0;
    }
    selected = false;
    setOriginalColour();
}

void lowCircle::setRadius(float r)
{

    float s = r/rad;
    this->rad = r;
    int x=0;int y=1;
        float coords[3];
        calcMidPoint(coords);

        for (int i=0;i<30;i+=3)
        {
            vertices[i] -= coords[0];
            vertices[i+1] -= coords[1];
            vertices[i+2] -= coords[2];

            vertices[i] *= s;
            vertices[i+1] *=(s);
            vertices[i+2] *=(s);

            vertices[i] += coords[0];
            vertices[i+1] += coords[1];
            vertices[i+2] += coords[2];
        }
   
}
void lowCircle::setMidPoint(float* a)
{
    vertices[0] = a[0];
    vertices[1] = a[1];
    vertices[2] = a[2];
    float p2= 2.0*M_PI;
    for (int i=1; i<10; i++)
    {
        float b = p2*i / 8;
        vertices[3*i]= rad*cos(b);
        vertices[3*i+1]= rad*sin(b);
        vertices[3*i+2]= 0;
    }
}

void lowCircle::setPastelColour()
{
    for (int i=0; i<30; i++)
    {
        col[i] = 0.6;
    }
    for (int i=0; i<30; i+=3)
    {
        col[i] = 1;
    }
}
void lowCircle::setOriginalColour()
{
    for (int i=0; i<30; i++)
    {
        col[i] = 0;
    }
    for (int i=0; i<30; i+=3)
    {
        col[i] = 1;
    }
}

void lowCircle::setColour(std::string c)
{
    colour currColour;
    if (c=="red")
    {
        currColour.setRed();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="pink")
    {
        currColour.setPink();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="blue")
    {
        currColour.setBlue();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="yellow")
    {
        currColour.setYellow();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="black")
    {
        currColour.setBlack();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="orange")
    {
        currColour.setOrange();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="white")
    {
        currColour.setWhite();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
    if (c=="darkOrange")
    {
        currColour.setDarkOrange();
        for (int i=0;i<30;i+=3)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
        }
    }
}
void lowCircle::select()
{
    selected=true;
    setPastelColour();
}
void lowCircle::deselect()
{
    selected = false;
    setOriginalColour();
}
void lowCircle::move(std::string direction,float d)
{
        if (direction=="up")
        {
            for (int i=1; i<30; i+=3)
            {
                
                vertices[i] += d;
            }
        }else if(direction=="down")
        {
            for (int i=1; i<30; i+=3)
            {
                vertices[i] -= d;
            }
        }else if (direction=="right")
        {
            for (int i=0; i<30; i+=3)
            {
                vertices[i] += d;
            }
        }else if (direction=="left")
        {
            for (int i=0; i<30; i+=3)
            {
                vertices[i] -= d;
            }
        }else if (direction=="incZ")
        {
            for (int i=2; i<30; i+=3)
            {
                vertices[i] += d;
            }
        }
        else if (direction=="decZ")
        {
            for (int i=2; i<30; i+=3)
            {
                vertices[i] -= d;
            }
        }
}
void lowCircle::scaleUp()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[3];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<30;i+=3)
        {
            vertices[i] -= coords[0];
            vertices[i+1] -= coords[1];
            vertices[i+2] -= coords[2];

            vertices[i] *= s;
            vertices[i+1] *= s;
            vertices[i+2] *= s;

            vertices[i] += coords[0];
            vertices[i+1] += coords[1];
            vertices[i+2] += coords[2];
        }
    }
}
void lowCircle::scaleDown()
{
    if (selected==true)
    {
        int x=0;int y=1;
        float coords[3];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<30;i+=3)
        {
            vertices[i] -= coords[0];
            vertices[i+1] -= coords[1];

            vertices[i] *= s;
            vertices[i+1] *= s;

            vertices[i] += coords[0];
            vertices[i+1] += coords[1];
        }
    }
}
void lowCircle::calcMidPoint(float* coordinates)
{
    coordinates[0] = vertices[0];
    coordinates[1] = vertices[1];
    coordinates[2] = vertices[2];
}
void lowCircle::rotateLeft()
{
    float angle=0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<30; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}
void lowCircle::rotateRight()
{
    float angle=-0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<30; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}



highCircle::highCircle()
{
    float rad=0.09;
    vertices[0] = 0; vertices[1]=0; vertices[2] =0; //x,y,z -> center of circle
    float p2= 2.0*M_PI;
    for (int i=1; i<60; i++)
    {
        float a = p2*i / 58;
        vertices[3*i]= rad*cos(a);
        vertices[3*i+1]= rad*sin(a);
        vertices[3*i+2]= 0;
    }
    selected = false;
    setOriginalColour();
}

void highCircle::setPastelColour()
{
    for (int i=0; i<180; i++)
    {
        col[i] = 0.3;
    }
    for (int i=0; i<180; i+=3)
    {
        col[i] = 1;
    }
    for (int i=1; i<180; i+=3)
    {
        col[i] = 0.5;
    }
}
void highCircle::setOriginalColour()
{
    for (int i=0; i<180; i++)
    {
        col[i] = 0;
    }
    for (int i=0; i<180; i+=3)
    {
        col[i] = 1;
    }
    for (int i=1; i<180; i+=3)
    {
        col[i] = 0.5;
    }
}
void highCircle::select()
{
    selected=true;
    setPastelColour();
}
void highCircle::deselect()
{
    selected = false;
    setOriginalColour();
}
void highCircle::move(std::string direction)
{
    float d = 0.02;
        if (direction=="up")
        {
            for (int i=1; i<180; i+=3)
            {
                vertices[i] += d;
            }
        }else if(direction=="down")
        {
            for (int i=1; i<180; i+=3)
            {
                vertices[i] -= d;
            }
        }else if (direction=="right")
        {
            for (int i=0; i<180; i+=3)
            {
                vertices[i] += d;
            }
        }else if (direction=="left")
        {
            for (int i=0; i<180; i+=3)
            {
                vertices[i] -= d;
            }
        }
}
void highCircle::scaleUp()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<180;i+=3)
        {
            vertices[i] -= coords[0];
            vertices[i+1] -= coords[1];

            vertices[i] *= s;
            vertices[i+1] *= s;

            vertices[i] += coords[0];
            vertices[i+1] += coords[1];
        }
    }
}
void highCircle::scaleDown()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<180;i+=3)
        {
            vertices[i] -= coords[0];
            vertices[i+1] -= coords[1];

            vertices[i] *= s;
            vertices[i+1] *= s;

            vertices[i] += coords[0];
            vertices[i+1] += coords[1];
        }
    }
}
void highCircle::calcMidPoint(float* coordinates)
{
    coordinates[0] = vertices[0];
    coordinates[1] = vertices[1];
}
void highCircle::rotateLeft()
{
    float angle=0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<180; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}
void highCircle::rotateRight()
{
    float angle=-0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<180; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}



rectangle::rectangle()
{
    tri1[0] = -0.2; tri1[1] =0.2;   tri1[2]=0;
    tri1[3] = 0;    tri1[4] =0.2;   tri1[5]=0;
    tri1[6] = -0.2;    tri1[7] =0.1;   tri1[8]=0;

    tri2[0] = 0; tri2[1] =0.2;   tri2[2]=0;
    tri2[3] = 0;    tri2[4] =0.1;   tri2[5]=0;
    tri2[6] = -0.2;    tri2[7] =0.1;   tri2[8]=0;
}
void rectangle::move(std::string direction,float d)
{
    //float d = 0.01;
        if (direction=="up")
        {
            tri1[1] += d;
            tri1[4] += d;
            tri1[7] += d;
            tri2[1] += d;
            tri2[4] += d;
            tri2[7] += d;
        }else if(direction=="down")
        {
            tri1[1] -= d;
            tri1[4] -= d;
            tri1[7] -= d;
            tri2[1] -= d;
            tri2[4] -= d;
            tri2[7] -= d;
        }else if (direction=="right")
        {
            tri1[0] += d;
            tri1[3] += d;
            tri1[6] += d;
            tri2[0] += d;
            tri2[3] += d;
            tri2[6] += d;
        }else if (direction=="left")
        {
            tri1[0] -= d;
            tri1[3] -= d;
            tri1[6] -= d;
            tri2[0] -= d;
            tri2[3] -= d;
            tri2[6] -= d;
        }else if (direction=="incZ")
        {
            tri1[2] += d;
            tri1[5] += d;
            tri1[8] += d;
            tri2[2] += d;
            tri2[5] += d;
            tri2[8] += d;
        }
        else if (direction=="decZ")
        {
            tri1[2] -= d;
            tri1[5] -= d;
            tri1[8] -= d;
            tri2[2] -= d;
            tri2[5] -= d;
            tri2[8] -= d;
        }
}
void rectangle::scaleUp()
{
    int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<8;i+=3)
        {
            //if (i!=2 || i!=5)
            {
                tri1[i] -= coords[x];
                tri1[i+1] -= coords[y];
                tri2[i] -= coords[x];
                tri2[i+1] -= coords[y];

                tri1[i] *= s;
                tri1[i+1] *= s;
                tri2[i] *= s;
                tri2[i+1] *= s;

                tri1[i] += coords[x];
                tri1[i+1] += coords[y];
                tri2[i] += coords[x];
                tri2[i+1] += coords[y];
            }
        }
}
void rectangle::scaleDown()
{
    int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<8;i+=3)
        {
            //if (i!=2 || i!=5)
            {
                tri1[i] -= coords[x];
                tri1[i+1] -= coords[y];
                tri2[i] -= coords[x];
                tri2[i+1] -= coords[y];

                tri1[i] *= s;
                tri1[i+1] *= s;
                tri2[i] *= s;
                tri2[i+1] *= s;

                tri1[i] += coords[x];
                tri1[i+1] += coords[y];
                tri2[i] += coords[x];
                tri2[i+1] += coords[y];
            }
        }
}
void rectangle::calcMidPoint(float* coordinates)
{
    int x=0; int y=1;
    coordinates[x]=0;
    coordinates[y]=0;
    for (int i=0; i<9 ;i+=3)
    {
        coordinates[x] += tri1[i] + tri2[i];
        coordinates[y] += tri1[i+y] + tri2[i+y];
    }
    coordinates[x] /= 6;
    coordinates[y] /= 6;
}

void rectangle::setPastelColour()
{
    for (int i=0;i<18;i++)
    {
        col[i] = 0.35;
    }
    for (int i=2;i<18;i+=3)
    {
        col[i] = 1;
    }
}
void rectangle::setOriginalColour()
{
    col[0] = 0;col[1] = 0;col[2] = 1;
    col[3] = 0;col[4] = 0;col[5] = 1;
    col[6] = 0;col[7] = 0;col[8] = 1;
    col[9] = 0;col[10] = 0;col[11] = 1;
    col[12] = 0;col[13] = 0;col[14] = 1;
    col[15] = 0;col[16] = 0;col[17] = 1;
    setOriginalColour();
}
void rectangle::setColour(std::string c,float a)
{
    colour currColour;
    currColour.setTransparency(a);
    
    if (c=="red")
    {
        currColour.setRed();
    }
    if (c=="orange")
    {
        currColour.setOrange();
    }
    if (c=="darkOrange")
    {
        currColour.setDarkOrange();
    }
    if (c=="yellow")
    {
        currColour.setYellow();
    }
    if (c=="green")
    {
        currColour.setGreen();
    }
    if (c=="blue")
    {
        currColour.setBlue();
    }
    if (c=="teal")
    {
        currColour.setTeal();
    }
    if (c=="purple")
    {
        currColour.setPurple();
    }
    if (c=="pink")
    {
        currColour.setPink();
    }
    if (c=="lightGrey")
    {
        currColour.setLightGrey();
    }
    if (c=="grey")
    {
        currColour.setGrey();
    }
    if (c=="darkGrey")
    {
        currColour.setDarkGrey();
    }
    if (c=="black")
    {
        currColour.setBlack();
    }
    if (c=="white")
    {
        currColour.setWhite();
    }
    
    for (int i=0;i<24;i+=4)
        {
            col[i] = currColour.col[0];
            col[i+1] = currColour.col[1];
            col[i+2] = currColour.col[2];
            col[i+3] = currColour.a[0];
        }
}
void rectangle::select()
{
    selected=true;
    setPastelColour();
}
void rectangle::deselect()
{
    selected = false;
    setOriginalColour();
}
void rectangle::rotateLeft()
{
    float angle=0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<9; i+=3)
    {
        tri1[i] -= coords[x];
        tri1[i+1] -= coords[y];
        tri2[i] -= coords[x];
        tri2[i+1] -= coords[y];

        float numx1 = tri1[i]*cos(angle) - tri1[i+1]*sin(angle);
        float numy1 = tri1[i]*sin(angle) + tri1[i+1]*cos(angle);
        float numx2 = tri2[i]*cos(angle) - tri2[i+1]*sin(angle);
        float numy2 = tri2[i]*sin(angle) + tri2[i+1]*cos(angle);

        tri1[i] = numx1 +coords[x];
        tri1[i+1] =numy1 +coords[y];
        tri2[i] = numx2 +coords[x];
        tri2[i+1] =numy2 +coords[y];
    }
}
void rectangle::rotateRight()
{
    float angle=-0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);
    

    for (int i=0; i<9; i+=3)
    {
        tri1[i] -= coords[x];
        tri1[i+1] -= coords[y];
        tri2[i] -= coords[x];
        tri2[i+1] -= coords[y];

        float numx1 = tri1[i]*cos(angle) - tri1[i+1]*sin(angle);
        float numy1 = tri1[i]*sin(angle) + tri1[i+1]*cos(angle);
        float numx2 = tri2[i]*cos(angle) - tri2[i+1]*sin(angle);
        float numy2 = tri2[i]*sin(angle) + tri2[i+1]*cos(angle);

        tri1[i] = numx1 +coords[x];
        tri1[i+1] =numy1 +coords[y];
        tri2[i] = numx2 +coords[x];
        tri2[i+1] =numy2 +coords[y];
    }
}