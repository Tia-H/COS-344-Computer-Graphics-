#include "seats.h"

triangleSeat::triangleSeat()
{
    vertex[0] = -0.1;vertex[1] =0.1;vertex[2]=0;
    vertex[3] = 0;vertex[4] =0.1;vertex[5]=0;
    vertex[6] = -0.1;vertex[7] =0.2;vertex[8]=0;
    selected = false;
    setOriginalColour();
}
void triangleSeat::setPastelColour()
{
    col[0] = 0.5;col[1] = 0.5;col[2] = 1;
    col[3] = 0.5;col[4] = 0.5;col[5] = 1;
    col[6] = 0.5;col[7] = 0.5;col[8] = 1;
}
void triangleSeat::setOriginalColour()
{
    col[0] = 0.5;col[1] = 0;col[2] = 1;
    col[3] = 0.5;col[4] = 0;col[5] = 1;
    col[6] = 0.5;col[7] = 0;col[8] = 1;
}

void triangleSeat::select()
{
    selected=true;
    setPastelColour();
}
void triangleSeat::deselect()
{
    selected = false;
    setOriginalColour();
}

void triangleSeat::move(std::string direction)
{
    float d = 0.02;
        if (direction=="up")
        {
            if (vertex[1]+d<0.9 && vertex[4]+d<0.9 && vertex[7]+d<0.9)
            {
                vertex[1] += d;
                vertex[4] += d;
                vertex[7] += d;
            }
        }else if(direction=="down")
        {
            if (vertex[1]-d>-0.9 && vertex[4]-d>-0.9 && vertex[7]-d>-0.9)
            {
                vertex[1] -= d;
                vertex[4] -= d;
                vertex[7] -= d;
            }
        }else if (direction=="right")
        {
            if (vertex[0]+d<0.9 && vertex[3]+d<0.9 && vertex[6]+d<0.9)
            {
                vertex[0] += d;
                vertex[3] += d;
                vertex[6] += d;
            }
        }else if (direction=="left")
        {
            if (vertex[0]-d>-0.9 && vertex[3]-d>-0.9 && vertex[6]-d>-0.9)
            {
                vertex[0] -= d;
                vertex[3] -= d;
                vertex[6] -= d;
            }
        }
}

void triangleSeat::scaleUp()
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
void triangleSeat::scaleDown()
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

void triangleSeat::calcMidPoint(float* coordinates)
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
void triangleSeat::rotateLeft()
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
void triangleSeat::rotateRight()
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
    /*

    SquareMatrix<3> point;
    point[0][0] = vertex[0];    point[0][1] = vertex[1];    point[0][2] = vertex[2];
    point[1][0] = vertex[3];    point[1][1] = vertex[4];    point[1][2] = vertex[5];
    point[2][0] = vertex[6];    point[2][1] = vertex[7];    point[2][2] = vertex[8];
    SquareMatrix<3> RotateM;
    RotateM[0][0] = cos(angle); RotateM[0][1] = -sin(angle);    RotateM[0][2] = 0;
    RotateM[1][0] = sin(angle); RotateM[1][1] = cos(angle);     RotateM[1][2] = 0;
    RotateM[2][0] = 0;          RotateM[2][1] = 0;              RotateM[2][2] = 1;

    SquareMatrix<3> point2; //T2
    point2[0][0] = 1;    point2[0][1] = 0;    point2[0][2] = coords[x];
    point2[1][0] = 0;    point2[1][1] = 1;    point2[1][2] = coords[y];
    point2[2][0] = 0;    point2[2][1] = 0;    point2[2][2] = 1;
    SquareMatrix<3> point3; //T1
    point3[0][0] = 1;    point3[0][1] = 0;    point3[0][2] = -coords[x];
    point3[1][0] = 0;    point3[1][1] = 1;    point3[1][2] = -coords[y];
    point3[2][0] = 0;    point3[2][1] = 0;    point3[2][2] = 1;
    
    Matrix<3,3> triM= point2*RotateM *point3;

    for (int i=0; i<6; i+=2)
    {
        Vector<3> vec;
        vec[0] = vertex[i];
        vec[1] = vertex[i+1];
        vec[2] = 1;

        //Matrix<3,1> vec1 = vec;
        //Matrix<3,1> m= triM*vec1;
        Vector<3> v1; 
        v1[0] = triM[0][0]*vec[0]+ triM[0][1]*vec[1]+triM[0][2]*vec[2];
        v1[1] = triM[1][0]*vec[0]+triM[1][1]*vec[1] + triM[1][2]*vec[2]; 
        v1[2] = triM[2][0]*vec[0] +triM[2][1]*vec[1]+triM[2][2]*vec[2];

        vertex[i] = v1[0];
        vertex[i+1] = v1[1];

    } */


}

squareSeat::squareSeat()
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

void squareSeat::setPastelColour()
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
void squareSeat::setOriginalColour()
{
    col[0] = 0;col[1] = 0;col[2] = 1;
    col[3] = 0;col[4] = 0;col[5] = 1;
    col[6] = 0;col[7] = 0;col[8] = 1;
    col[9] = 0;col[10] = 0;col[11] = 1;
    col[12] = 0;col[13] = 0;col[14] = 1;
    col[15] = 0;col[16] = 0;col[17] = 1;
}
void squareSeat::select()
{
    selected=true;
    setPastelColour();
}
void squareSeat::deselect()
{
    selected = false;
    setOriginalColour();
}
void squareSeat::move(std::string direction)
{
    float d = 0.02;
        if (direction=="up")
        {
            if (tri1[1]+d<0.9 && tri1[4]+d<0.9 && tri1[7]+d<0.9 && tri2[1]+d<0.9 && tri2[4]+d<0.9 && tri2[7]+d<0.9)
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
            if (tri1[1]-d>-0.9 && tri1[4]-d>-0.9 && tri1[7]-d>-0.9 && tri2[1]-d>-0.9 && tri2[4]-d>-0.9 && tri2[7]-d>-0.9)
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
            if (tri1[0]+d<0.9 && tri1[3]+d<0.9 && tri1[6]+d<0.9 && tri2[0]+d<0.9 && tri2[3]+d<0.9 && tri2[6]+d<0.9)
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
            if (tri1[0]-d>-0.9 && tri1[3]-d>-0.9 && tri1[6]-d>-0.9 && tri2[0]-d>-0.9 && tri2[3]-d>-0.9 && tri2[6]-d>-0.9)
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
void squareSeat::scaleUp()
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
void squareSeat::scaleDown()
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
void squareSeat::calcMidPoint(float* coordinates)
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
void squareSeat::rotateLeft()
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
void squareSeat::rotateRight()
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


circleSeat::circleSeat()
{
    float rad=0.07;
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

void circleSeat::setPastelColour()
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
void circleSeat::setOriginalColour()
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
void circleSeat::select()
{
    selected=true;
    setPastelColour();
}
void circleSeat::deselect()
{
    selected = false;
    setOriginalColour();
}
void circleSeat::move(std::string direction)
{
    float d = 0.02;
    bool reverse=false;
        if (direction=="up")
        {
            for (int i=1; i<30; i+=3)
            {
                if (vertices[i]+d>0.9)
                {
                    reverse=true;
                }
                vertices[i] += d;
            }
            if (reverse==true)
            {
                for (int i=1; i<30; i+=3)
                {
                    vertices[i] -= d;
                }
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
        }
}
void circleSeat::scaleUp()
{
    if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
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
void circleSeat::scaleDown()
{
    if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
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
void circleSeat::calcMidPoint(float* coordinates)
{
    coordinates[0] = vertices[0];
    coordinates[1] = vertices[1];
}
void circleSeat::rotateLeft()
{

}
void circleSeat::rotateRight()
{

}

highCircleSeat::highCircleSeat()
{
    float rad=0.07;
    vertices[0] = 0; vertices[1]=0; vertices[2] =0; //x,y,z -> center of circle
    float p2= 2.0*M_PI;
    for (int i=1; i<50; i++)
    {
        float a = p2*i / 48;
        vertices[3*i]= rad*cos(a);
        vertices[3*i+1]= rad*sin(a);
        vertices[3*i+2]= 0;
    }
    selected = false;
    setOriginalColour();
}

void highCircleSeat::setPastelColour()
{
    for (int i=0; i<150; i++)
    {
        col[i] = 1;
    }
    for (int i=2; i<150; i+=3)
    {
        col[i] = 0.5;
    }
}
void highCircleSeat::setOriginalColour()
{
    for (int i=0; i<150; i++)
    {
        col[i] = 1;
    }
    for (int i=2; i<150; i+=3)
    {
        col[i] = 0;
    }
}
void highCircleSeat::select()
{
    selected=true;
    setPastelColour();
}
void highCircleSeat::deselect()
{
    selected = false;
    setOriginalColour();
}
void highCircleSeat::move(std::string direction)
{
    float d = 0.02;
        if (direction=="up")
        {
            for (int i=1; i<150; i+=3)
            {
                vertices[i] += d;
            }
        }else if(direction=="down")
        {
            for (int i=1; i<150; i+=3)
            {
                vertices[i] -= d;
            }
        }else if (direction=="right")
        {
            for (int i=0; i<150; i+=3)
            {
                vertices[i] += d;
            }
        }else if (direction=="left")
        {
            for (int i=0; i<150; i+=3)
            {
                vertices[i] -= d;
            }
        }
}
void highCircleSeat::scaleUp()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<150;i+=3)
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
void highCircleSeat::scaleDown()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<150;i+=3)
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
void highCircleSeat::calcMidPoint(float* coordinates)
{
    coordinates[0] = vertices[0];
    coordinates[1] = vertices[1];
}
void highCircleSeat::rotateLeft()
{

}
void highCircleSeat::rotateRight()
{

}

higherCircleSeat::higherCircleSeat()
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

void higherCircleSeat::setPastelColour()
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
void higherCircleSeat::setOriginalColour()
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
void higherCircleSeat::select()
{
    selected=true;
    setPastelColour();
}
void higherCircleSeat::deselect()
{
    selected = false;
    setOriginalColour();
}
void higherCircleSeat::move(std::string direction)
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
void higherCircleSeat::scaleUp()
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
void higherCircleSeat::scaleDown()
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
void higherCircleSeat::calcMidPoint(float* coordinates)
{
    coordinates[0] = vertices[0];
    coordinates[1] = vertices[1];
}
void higherCircleSeat::rotateLeft()
{

}
void higherCircleSeat::rotateRight()
{

}

trianglePlant::trianglePlant()
{
    vertex[0] = -0.05;vertex[1] =0.1;vertex[2]=0;
    vertex[3] = 0;vertex[4] =0.1;vertex[5]=0;
    vertex[6] = -0.05;vertex[7] =0;vertex[8]=0;
    selected = false;
    setOriginalColour();
}
void trianglePlant::setPastelColour()
{
    col[0] = 0.6;col[1] = 1;col[2] = 0.6;
    col[3] = 0.6;col[4] = 1;col[5] = 0.6;
    col[6] = 0.6;col[7] = 1;col[8] = 0.6;
}
void trianglePlant::setOriginalColour()
{
    col[0] = 0;col[1] = 1;col[2] = 0;
    col[3] = 0;col[4] = 1;col[5] = 0;
    col[6] = 0;col[7] = 1;col[8] = 0;
}

void trianglePlant::select()
{
    selected=true;
    setPastelColour();
}
void trianglePlant::deselect()
{
    selected = false;
    setOriginalColour();
}

void trianglePlant::move(std::string direction)
{
    float d = 0.02;
    if (direction=="up")
    {
        if (vertex[1]+d<0.9 && vertex[4]+d<0.9 && vertex[7]+d<0.9)
        {
            vertex[1] += d;
            vertex[4] += d;
            vertex[7] += d;
        }
    }else if(direction=="down")
    {
        if (vertex[1]-d>-0.9 && vertex[4]-d>-0.9 && vertex[7]-d>-0.9)
        {
            vertex[1] -= d;
            vertex[4] -= d;
            vertex[7] -= d;
        }
    }else if (direction=="right")
    {
        if (vertex[0]+d<0.9 && vertex[3]+d<0.9 && vertex[6]+d<0.9)
        {
            vertex[0] += d;
            vertex[3] += d;
            vertex[6] += d;
        }
    }else if (direction=="left")
    {
        if (vertex[0]-d>-0.9 && vertex[3]-d>-0.9 && vertex[6]-d>-0.9)
        {
            vertex[0] -= d;
            vertex[3] -= d;
            vertex[6] -= d;
        }
    }
}

void trianglePlant::scaleUp()
{
    if (selected==true)
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
void trianglePlant::scaleDown()
{
    if (selected==true)
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

void trianglePlant::calcMidPoint(float* coordinates)
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
void trianglePlant::rotateLeft()
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
void trianglePlant::rotateRight()
{
    float angle=-0.1;
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


circleTable::circleTable()
{
    float rad=0.09;
    vertices[0] = 0; vertices[1]=0; vertices[2] =0; //x,y,z -> center of circle
    float p2= 2.0*M_PI;
    for (int i=1; i<8; i++)
    {
        float a = p2*i / 6;
        vertices[3*i]= rad*cos(a);
        vertices[3*i+1]= rad*sin(a);
        vertices[3*i+2]= 0;
    }
    selected = false;
    setOriginalColour();
}

void circleTable::setPastelColour()
{
    for (int i=0; i<24; i++)
    {
        col[i] = 1;
    }
    for (int i=1; i<24; i+=3)
    {
        col[i] = 0.5;
    }
}
void circleTable::setOriginalColour()
{
    for (int i=0; i<24; i++)
    {
        col[i] = 1;
    }
    for (int i=1; i<24; i+=3)
    {
        col[i] = 0;
    }
}
void circleTable::select()
{
    selected=true;
    setPastelColour();
}
void circleTable::deselect()
{
    selected = false;
    setOriginalColour();
}
void circleTable::move(std::string direction)
{
    float d = 0.02;
    bool reverse=false;
        if (direction=="up")
        {
            for (int i=1; i<24; i+=3)
            {
                if (vertices[i]+d>0.9)
                {
                    reverse=true;
                }
                vertices[i] += d;
            }
            if (reverse==true)
            {
                for (int i=1; i<24; i+=3)
                {
                    vertices[i] -= d;
                }
            }
        }else if(direction=="down")
        {
            for (int i=1; i<24; i+=3)
            {
                if (vertices[i]-d<-0.9)
                {
                    reverse=true;
                }
                vertices[i] -= d;
            }
            if (reverse==true)
            {
                for (int i=1; i<24; i+=3)
                {
                    vertices[i] += d;
                }
            }
        }else if (direction=="right")
        {
            for (int i=0; i<24; i+=3)
            {
                if (vertices[i]+d>0.9)
                {
                    reverse=true;
                }
                vertices[i] += d;
            }
            if (reverse==true)
            {
                for (int i=0; i<24; i+=3)
                {
                    vertices[i] -= d;
                }
            }
        }else if (direction=="left")
        {
            for (int i=0; i<24; i+=3)
            {
                if (vertices[i]-d<-0.9)
                {
                    reverse=true;
                }
                vertices[i] -= d;
            }
            if (reverse==true)
            {
                for (int i=0; i<24; i+=3)
                {
                    vertices[i] += d;
                }
            }
        }
}
void circleTable::scaleUp()
{
    if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<24;i+=3)
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
void circleTable::scaleDown()
{
    if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<24;i+=3)
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
void circleTable::calcMidPoint(float* coordinates)
{
    coordinates[0] = vertices[0];
    coordinates[1] = vertices[1];
}
void circleTable::rotateLeft()
{
    float angle=0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<24; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}
void circleTable::rotateRight()
{
    float angle=-0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<24; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}


Rectangle::Rectangle()
{
    tri1[0] = -0.2; tri1[1] =0.2;   tri1[2]=0;
    tri1[3] = 0;    tri1[4] =0.2;   tri1[5]=0;
    tri1[6] = -0.2;    tri1[7] =0.1;   tri1[8]=0;

    tri2[0] = 0; tri2[1] =0.2;   tri2[2]=0;
    tri2[3] = 0;    tri2[4] =0.1;   tri2[5]=0;
    tri2[6] = -0.2;    tri2[7] =0.1;   tri2[8]=0;
}
void Rectangle::move(std::string direction)
{
    float d = 0.02;
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
        }
}
void Rectangle::scaleUp()
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
void Rectangle::scaleDown()
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
void Rectangle::calcMidPoint(float* coordinates)
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

Square::Square()
{
    tri1[0] = -0.1; tri1[1] =0.1;   tri1[2]=0;
    tri1[3] = 0.1;    tri1[4] =0.1;   tri1[5]=0;
    tri1[6] = -0.1;    tri1[7] =-0.1;   tri1[8]=0;

    tri2[0] = 0.1;    tri2[1] =0.1;   tri2[2]=0;
    tri2[3] = 0.1;    tri2[4] =-0.1;   tri2[5]=0;
    tri2[6] = -0.1;    tri2[7] =-0.1;   tri2[8]=0;
}
void Square::move(std::string direction)
{
    float d = 0.02;
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
        }
}
void Square::scaleUp()
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
void Square::scaleDown()
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
void Square::calcMidPoint(float* coordinates)
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


bin::bin()
{
    float rad=0.05;
    vertices[0] = 0; vertices[1]=0; vertices[2] =0; //x,y,z -> center of circle
    float p2= 2.0*M_PI;
    for (int i=1; i<51; i++)
    {
        float a = p2*i / 49;
        vertices[3*i]= rad*cos(a);
        vertices[3*i+1]= rad*sin(a);
        vertices[3*i+2]= 0;
    }
    selected = false;
    setOriginalColour();
}

void bin::setPastelColour()
{
    for (int i=0; i<153; i++)
    {
        col[i] = 0.4;
    }
}
void bin::setOriginalColour()
{
    for (int i=0; i<153; i++)
    {
        col[i] = 0.1;
    }
}
void bin::select()
{
    selected=true;
    setPastelColour();
}
void bin::deselect()
{
    selected = false;
    setOriginalColour();
}
void bin::move(std::string direction)
{
    bool reverse=false;
    float d = 0.02;
        if (direction=="up")
        {
            for (int i=1; i<153; i+=3)
            {
                if (vertices[i]+d>0.9)
                {
                    reverse=true;
                }
                vertices[i] += d;
            }
            if (reverse==true)
            {
                for (int i=1; i<153; i+=3)
                {
                    vertices[i] -= d;
                }
            }
        }else if(direction=="down")
        {
            for (int i=1; i<153; i+=3)
            {
                if (vertices[i]-d<-0.9)
                {
                    reverse=true;
                }
                vertices[i] -= d;
            }
            if (reverse==true)
            {
                for (int i=1; i<153; i+=3)
                {
                    vertices[i] += d;
                }
            }
        }else if (direction=="right")
        {
            for (int i=0; i<153; i+=3)
            {
                if (vertices[i]+d>0.9)
                {
                    reverse=true;
                }
                vertices[i] += d;
            }
            if (reverse==true)
            {
                for (int i=0; i<153; i+=3)
                {
                    vertices[i] -= d;
                }
            }
        }else if (direction=="left")
        {
            for (int i=0; i<153; i+=3)
            {
                if (vertices[i]-d<-0.9)
                {
                    reverse=true;
                }
                vertices[i] -= d;
            }
            if (reverse==true)
            {
                for (int i=0; i<153; i+=3)
                {
                    vertices[i] += d;
                }
            }
        }
}
void bin::scaleUp()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=1.1;
        for (int i=0;i<153;i+=3)
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
void bin::scaleDown()
{
    //if (selected==true)
    {
        int x=0;int y=1;
        float coords[2];
        calcMidPoint(coords);

        float s=0.9;
        for (int i=0;i<153;i+=3)
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
void bin::calcMidPoint(float* coordinates)
{
    coordinates[0] = vertices[0];
    coordinates[1] = vertices[1];
}
void bin::rotateLeft()
{
    float angle=0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<153; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}
void bin::rotateRight()
{
    float angle=-0.1;
    int x=0;int y=1;
    float coords[2];
    calcMidPoint(coords);

    for (int i=0; i<153; i+=3)
    {
        vertices[i] -= coords[x];
        vertices[i+1] -= coords[y];

        float numx = vertices[i]*cos(angle) - vertices[i+1]*sin(angle);
        float numy = vertices[i]*sin(angle) + vertices[i+1]*cos(angle);

        vertices[i] = numx +coords[x];
        vertices[i+1] =numy +coords[y];
    }
}