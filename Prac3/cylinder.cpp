#include "shapes3D.h"

cylinder::cylinder()
{
    float mid[3];
    mid[0] = -0.1;
    mid[1] = 0.03;
    mid[2] = 0;
    width =0.3;
    degree = 0.1;
    /*top.setMidPoint(mid);
    width =0.3;

    mid[0] += width;
    bottom.setMidPoint(mid);*/
    for (int i=0;i<30;i+=3)
    {
        top.vertices[i+2] = top.vertices[i];
        top.vertices[i] = 0;

        bottom.vertices[i+2] = bottom.vertices[i];
        bottom.vertices[i] = width;
    }
    changeVertices();
    updateVertices();

    setColour("orange");
}

void cylinder::changeVertices()
{

    for (int i=0;i<9;i+=3)
    {
        r1.tri1[i] = top.vertices[i+3];
        r1.tri1[i+1] = top.vertices[i+3+1];
        r1.tri1[i+2] = top.vertices[i+3+2];
        r1.tri2[i] = top.vertices[i+6];
        r1.tri2[i+1] = top.vertices[i+6+1];
        r1.tri2[i+2] = top.vertices[i+6+2];

        r2.tri1[i] = top.vertices[i+6];
        r2.tri1[i+1] = top.vertices[i+6+1];
        r2.tri1[i+2] = top.vertices[i+6+2];
        r2.tri2[i] = top.vertices[i+9];
        r2.tri2[i+1] = top.vertices[i+9+1];
        r2.tri2[i+2] = top.vertices[i+9+2];

        r3.tri1[i] = top.vertices[i+9];
        r3.tri1[i+1] = top.vertices[i+9+1];
        r3.tri1[i+2] = top.vertices[i+9+2];
        r3.tri2[i] = top.vertices[i+12];
        r3.tri2[i+1] = top.vertices[i+12+1];
        r3.tri2[i+2] = top.vertices[i+12+2];

        r4.tri1[i] = top.vertices[i+12];
        r4.tri1[i+1] = top.vertices[i+12+1];
        r4.tri1[i+2] = top.vertices[i+12+2];
        r4.tri2[i] = top.vertices[i+15];
        r4.tri2[i+1] = top.vertices[i+15+1];
        r4.tri2[i+2] = top.vertices[i+15+2];

        r5.tri1[i] = top.vertices[i+15];
        r5.tri1[i+1] = top.vertices[i+15+1];
        r5.tri1[i+2] = top.vertices[i+15+2];
        r5.tri2[i] = top.vertices[i+18];
        r5.tri2[i+1] = top.vertices[i+18+1];
        r5.tri2[i+2] = top.vertices[i+18+2];

        r6.tri1[i] = top.vertices[i+18];
        r6.tri1[i+1] = top.vertices[i+18+1];
        r6.tri1[i+2] = top.vertices[i+18+2];
        r6.tri2[i] = top.vertices[i+21];
        r6.tri2[i+1] = top.vertices[i+21+1];
        r6.tri2[i+2] = top.vertices[i+21+2];

        r7.tri1[i] = top.vertices[i+21];
        r7.tri1[i+1] = top.vertices[i+21+1];
        r7.tri1[i+2] = top.vertices[i+21+2];
        r7.tri2[i] = top.vertices[i+24];
        r7.tri2[i+1] = top.vertices[i+24+1];
        r7.tri2[i+2] = top.vertices[i+24+2];

        r8.tri1[i] = top.vertices[i+24];
        r8.tri1[i+1] = top.vertices[i+24+1];
        r8.tri1[i+2] = top.vertices[i+24+2];
        r8.tri2[i] = top.vertices[i+27];
        r8.tri2[i+1] = top.vertices[i+27+1];
        r8.tri2[i+2] = top.vertices[i+27+2];
    }
    for (int i=3;i<9;i+=3)
    {
        r1.tri2[i] = bottom.vertices[i];
        r1.tri2[i+1] = bottom.vertices[i+1];
        r1.tri2[i+2] = bottom.vertices[i+2];

        r2.tri2[i] = bottom.vertices[i+3];
        r2.tri2[i+1] = bottom.vertices[i+1+3];
        r2.tri2[i+2] = bottom.vertices[i+2+3];

        r3.tri2[i] = bottom.vertices[i+6];
        r3.tri2[i+1] = bottom.vertices[i+1+6];
        r3.tri2[i+2] = bottom.vertices[i+2+6];

        r4.tri2[i] = bottom.vertices[i+9];
        r4.tri2[i+1] = bottom.vertices[i+1+9];
        r4.tri2[i+2] = bottom.vertices[i+2+9];

        r5.tri2[i] = bottom.vertices[i+12];
        r5.tri2[i+1] = bottom.vertices[i+1+12];
        r5.tri2[i+2] = bottom.vertices[i+2+12];

        r6.tri2[i] = bottom.vertices[i+15];
        r6.tri2[i+1] = bottom.vertices[i+1+15];
        r6.tri2[i+2] = bottom.vertices[i+2+15];

        r7.tri2[i] = bottom.vertices[i+18];
        r7.tri2[i+1] = bottom.vertices[i+1+18];
        r7.tri2[i+2] = bottom.vertices[i+2+18];

        r8.tri2[i] = bottom.vertices[i+21];
        r8.tri2[i+1] = bottom.vertices[i+1+21];
        r8.tri2[i+2] = bottom.vertices[i+2+21];
    }
    for (int i=6;i<9;i+=3)
    {
        r1.tri1[i] = bottom.vertices[i-3];
        r1.tri1[i+1] = bottom.vertices[i-3+1];
        r1.tri1[i+2] = bottom.vertices[i-3+2];

        r2.tri1[i] = bottom.vertices[i];
        r2.tri1[i+1] = bottom.vertices[i+1];
        r2.tri1[i+2] = bottom.vertices[i+2];

        r3.tri1[i] = bottom.vertices[i+3];
        r3.tri1[i+1] = bottom.vertices[i+1+3];
        r3.tri1[i+2] = bottom.vertices[i+2+3];

        r4.tri1[i] = bottom.vertices[i+6];
        r4.tri1[i+1] = bottom.vertices[i+1+6];
        r4.tri1[i+2] = bottom.vertices[i+2+6];

        r5.tri1[i] = bottom.vertices[i+9];
        r5.tri1[i+1] = bottom.vertices[i+1+9];
        r5.tri1[i+2] = bottom.vertices[i+2+9];

        r6.tri1[i] = bottom.vertices[i+12];
        r6.tri1[i+1] = bottom.vertices[i+1+12];
        r6.tri1[i+2] = bottom.vertices[i+2+12];

        r7.tri1[i] = bottom.vertices[i+15];
        r7.tri1[i+1] = bottom.vertices[i+1+15];
        r7.tri1[i+2] = bottom.vertices[i+2+15];

        r8.tri1[i] = bottom.vertices[i+18];
        r8.tri1[i+1] = bottom.vertices[i+1+18];
        r8.tri1[i+2] = bottom.vertices[i+2+18];

    }
}

void cylinder::updateVertices()
{
    for (int i=0;i<30;i++)
    {
        vertices[i] = top.vertices[i];
        vertices[i+30] = bottom.vertices[i];
    }
    for (int i=0;i<9;i++)
    {
        vertices[i+60] = r1.tri1[i];
        vertices[i+69] = r1.tri2[i];
        vertices[i+78] = r2.tri1[i];
        vertices[i+87] = r2.tri2[i];
        vertices[i+96] = r3.tri1[i];
        vertices[i+105] = r3.tri2[i];
        vertices[i+114] = r4.tri1[i];
        vertices[i+123] = r4.tri2[i];
        vertices[i+132] = r5.tri1[i];
        vertices[i+141] = r5.tri2[i];
        vertices[i+150] = r6.tri1[i];
        vertices[i+159] = r6.tri2[i];
        vertices[i+168] = r7.tri1[i];
        vertices[i+177] = r7.tri2[i];
        vertices[i+186] = r8.tri1[i];
        vertices[i+195] = r8.tri2[i];
    }
}

void cylinder::setColour(std::string col)
{
    top.setColour(col);
            bottom.setColour(col);
            r1.setColour(col);
            r2.setColour(col);
            r3.setColour(col);
            r4.setColour(col);
            r5.setColour(col);
            r6.setColour(col);
            r7.setColour(col);
            r8.setColour(col);

    for (int i=0;i<30;i++)
    {
        colours[i] = top.col[i];
        colours[i+30] = bottom.col[i];
    }
    for (int i=0;i<18;i++)
    {
        colours[i+60] = r1.col[i];
        colours[i+78] = r2.col[i];
        colours[i+96] = r3.col[i];
        colours[i+114] = r4.col[i];
        colours[i+132] = r5.col[i];
        colours[i+150] = r6.col[i];
        colours[i+168] = r7.col[i];
        colours[i+186] = r8.col[i];
    }
}

void cylinder::setWidth(float width)
{
    this->width = width;
    for (int i=0;i<30;i+=3)
    {
        bottom.vertices[i] = width;
    }
    changeVertices();
    updateVertices();

}
void cylinder::setRadius(float r)
{
    top.setRadius(r);
    bottom.setRadius(r);
    changeVertices();
    updateVertices();
}

void cylinder::setDegree(float d)
{
    degree=d;
}

void cylinder::setMidPoint(float* mid)
{
    float z = mid[2];
    float r = width/2;
    mid[2] = z+r;

    top.setMidPoint(mid);
    mid[2] = z-r;
    bottom.setMidPoint(mid);
    changeVertices();
    updateVertices();
}

void cylinder::calcMidPoint(float* coordinates)
{
    int x=0; int y=1;int z=2;
    coordinates[x]=0;
    coordinates[y]=0;
    coordinates[z]=0;

        coordinates[x] = top.vertices[0] + bottom.vertices[0];
        coordinates[y] = top.vertices[1]+ bottom.vertices[1];
        coordinates[z] = top.vertices[2] +bottom.vertices[2];
  
    coordinates[x] /= 2;
    coordinates[y] /= 2;
    coordinates[z] /= 2;
}

void cylinder::rotateLeftX(float* mid)
{

    float angle=degree;
    float coords[3];
    //calcMidPoint(coords);
    coords[0] = mid[0];
    coords[1] = mid[1];
    coords[2] = mid[2];

    IdentityMatrix<4> Origin;
    Origin[0][3] = coords[0];
    Origin[1][3] = coords[1];
    Origin[2][3] = coords[2];

    IdentityMatrix<4> T;
    T[0][3] = -1*coords[0];
    T[1][3] = -1*coords[1];
    T[2][3] = -1*coords[2];

    IdentityMatrix<4> R;
    R[0][0]=1;
    R[1][1]= cos(angle);
    R[1][2]= -1*sin(angle);
    R[2][1]= sin(angle);
    R[2][2]= cos(angle);
    R[3][3]=1;

    Matrix<4,4> rotationM;
    rotationM = Origin*R*T;

    //mulitply rotationM with each vertex in shape
    multiplyMcircle(rotationM,top.vertices);
    multiplyMcircle(rotationM,bottom.vertices);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);
    multiplyM(rotationM,r4.tri1);
    multiplyM(rotationM,r4.tri2);
    multiplyM(rotationM,r5.tri1);
    multiplyM(rotationM,r5.tri2);
    multiplyM(rotationM,r6.tri1);
    multiplyM(rotationM,r6.tri2);
    multiplyM(rotationM,r7.tri1);
    multiplyM(rotationM,r7.tri2);
    multiplyM(rotationM,r8.tri1);
    multiplyM(rotationM,r8.tri2);

    updateVertices();
}
void cylinder::rotateRightX(float* mid)
{
    float angle=-1*degree;
    float coords[3];
    //calcMidPoint(coords);
    coords[0] = mid[0];
    coords[1] = mid[1];
    coords[2] = mid[2];


    IdentityMatrix<4> Origin;
    Origin[0][3] = coords[0];
    Origin[1][3] = coords[1];
    Origin[2][3] = coords[2];

    IdentityMatrix<4> T;
    T[0][3] = -1*coords[0];
    T[1][3] = -1*coords[1];
    T[2][3] = -1*coords[2];

    IdentityMatrix<4> R;
    R[0][0]=1;
    R[1][1]= cos(angle);
    R[1][2]= -1*sin(angle);
    R[2][1]= sin(angle);
    R[2][2]= cos(angle);
    R[3][3]=1;

    Matrix<4,4> rotationM;
    rotationM = Origin*R*T;

    //mulitply rotationM with each vertex in shape
    multiplyMcircle(rotationM,top.vertices);
    multiplyMcircle(rotationM,bottom.vertices);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);
    multiplyM(rotationM,r4.tri1);
    multiplyM(rotationM,r4.tri2);
    multiplyM(rotationM,r5.tri1);
    multiplyM(rotationM,r5.tri2);
    multiplyM(rotationM,r6.tri1);
    multiplyM(rotationM,r6.tri2);
    multiplyM(rotationM,r7.tri1);
    multiplyM(rotationM,r7.tri2);
    multiplyM(rotationM,r8.tri1);
    multiplyM(rotationM,r8.tri2);

    updateVertices();
}
void cylinder::rotateLeftY(float* mid)
{
    float angle=degree;
    float coords[3];
    //calcMidPoint(coords);
    coords[0] = mid[0];
    coords[1] = mid[1];
    coords[2] = mid[2];

    IdentityMatrix<4> Origin;
    Origin[0][3] = coords[0];
    Origin[1][3] = coords[1];
    Origin[2][3] = coords[2];

    IdentityMatrix<4> T;
    T[0][3] = -1*coords[0];
    T[1][3] = -1*coords[1];
    T[2][3] = -1*coords[2];

    IdentityMatrix<4> R;
    R[0][0]= cos(angle);
    R[0][2]= sin(angle);
    R[1][1]= 1;
    R[2][0]= -1*sin(angle);
    R[2][2]= cos(angle);
    R[3][3]= 1;

    Matrix<4,4> rotationM;
    rotationM = Origin*R*T;

    //mulitply rotationM with each vertex in shape
    multiplyMcircle(rotationM,top.vertices);
    multiplyMcircle(rotationM,bottom.vertices);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);
    multiplyM(rotationM,r4.tri1);
    multiplyM(rotationM,r4.tri2);
    multiplyM(rotationM,r5.tri1);
    multiplyM(rotationM,r5.tri2);
    multiplyM(rotationM,r6.tri1);
    multiplyM(rotationM,r6.tri2);
    multiplyM(rotationM,r7.tri1);
    multiplyM(rotationM,r7.tri2);
    multiplyM(rotationM,r8.tri1);
    multiplyM(rotationM,r8.tri2);

    updateVertices();
}
void cylinder::rotateRightY(float* mid)
{
    float angle=-1*degree;
    float coords[3];
    //calcMidPoint(coords);
    coords[0] = mid[0];
    coords[1] = mid[1];
    coords[2] = mid[2];

    IdentityMatrix<4> Origin;
    Origin[0][3] = coords[0];
    Origin[1][3] = coords[1];
    Origin[2][3] = coords[2];

    IdentityMatrix<4> T;
    T[0][3] = -1*coords[0];
    T[1][3] = -1*coords[1];
    T[2][3] = -1*coords[2];

    IdentityMatrix<4> R;
    R[0][0]= cos(angle);
    R[0][2]= sin(angle);
    R[1][1]= 1;
    R[2][0]= -1*sin(angle);
    R[2][2]= cos(angle);
    R[3][3]= 1;

    Matrix<4,4> rotationM;
    rotationM = Origin*R*T;

    //mulitply rotationM with each vertex in shape
    multiplyMcircle(rotationM,top.vertices);
    multiplyMcircle(rotationM,bottom.vertices);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);
    multiplyM(rotationM,r4.tri1);
    multiplyM(rotationM,r4.tri2);
    multiplyM(rotationM,r5.tri1);
    multiplyM(rotationM,r5.tri2);
    multiplyM(rotationM,r6.tri1);
    multiplyM(rotationM,r6.tri2);
    multiplyM(rotationM,r7.tri1);
    multiplyM(rotationM,r7.tri2);
    multiplyM(rotationM,r8.tri1);
    multiplyM(rotationM,r8.tri2);

    updateVertices();
}

void cylinder::rotateLeftZ(float* mid)
{
    float angle=degree;
    float coords[3];
    //calcMidPoint(coords);
    coords[0] = mid[0];
    coords[1] = mid[1];
    coords[2] = mid[2];

    IdentityMatrix<4> Origin;
    Origin[0][3] = coords[0];
    Origin[1][3] = coords[1];
    Origin[2][3] = coords[2];

    IdentityMatrix<4> T;
    T[0][3] = -1*coords[0];
    T[1][3] = -1*coords[1];
    T[2][3] = -1*coords[2];

    IdentityMatrix<4> R;
    R[0][0]= cos(angle);
    R[0][1]= -1*sin(angle);
    R[1][0]= sin(angle);
    R[1][1]= cos(angle);
    R[2][2]= 1;
    R[3][3]= 1;

    Matrix<4,4> rotationM;
    rotationM = Origin*R*T;

    //mulitply rotationM with each vertex in shape
    multiplyMcircle(rotationM,top.vertices);
    multiplyMcircle(rotationM,bottom.vertices);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);
    multiplyM(rotationM,r4.tri1);
    multiplyM(rotationM,r4.tri2);
    multiplyM(rotationM,r5.tri1);
    multiplyM(rotationM,r5.tri2);
    multiplyM(rotationM,r6.tri1);
    multiplyM(rotationM,r6.tri2);
    multiplyM(rotationM,r7.tri1);
    multiplyM(rotationM,r7.tri2);
    multiplyM(rotationM,r8.tri1);
    multiplyM(rotationM,r8.tri2);

    updateVertices();
}

void cylinder::rotateRightZ(float* mid)
{
    float angle=-1*degree;
    float coords[3];
    //calcMidPoint(coords);
    coords[0] = mid[0];
    coords[1] = mid[1];
    coords[2] = mid[2];

    IdentityMatrix<4> Origin;
    Origin[0][3] = coords[0];
    Origin[1][3] = coords[1];
    Origin[2][3] = coords[2];

    IdentityMatrix<4> T;
    T[0][3] = -1*coords[0];
    T[1][3] = -1*coords[1];
    T[2][3] = -1*coords[2];

    IdentityMatrix<4> R;
    R[0][0]= cos(angle);
    R[0][1]= -1*sin(angle);
    R[1][0]= sin(angle);
    R[1][1]= cos(angle);
    R[2][2]= 1;
    R[3][3]= 1;

    Matrix<4,4> rotationM;
    rotationM = Origin*R*T;

    //mulitply rotationM with each vertex in shape
    multiplyMcircle(rotationM,top.vertices);
    multiplyMcircle(rotationM,bottom.vertices);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);
    multiplyM(rotationM,r4.tri1);
    multiplyM(rotationM,r4.tri2);
    multiplyM(rotationM,r5.tri1);
    multiplyM(rotationM,r5.tri2);
    multiplyM(rotationM,r6.tri1);
    multiplyM(rotationM,r6.tri2);
    multiplyM(rotationM,r7.tri1);
    multiplyM(rotationM,r7.tri2);
    multiplyM(rotationM,r8.tri1);
    multiplyM(rotationM,r8.tri2);

    updateVertices();
}

void cylinder::move(std::string d)
{
    top.move(d,0.01);
    bottom.move(d,0.01);
    r1.move(d);
    r2.move(d);
    r3.move(d);
    r4.move(d);
    r5.move(d);
    r6.move(d);
    r7.move(d);
    r8.move(d);

    updateVertices();
}

void cylinder::move(std::string d,float n)
{
    top.move(d,n);
    bottom.move(d,n);
    r1.move(d,n);
    r2.move(d,n);
    r3.move(d,n);
    r4.move(d);
    r5.move(d);
    r6.move(d);
    r7.move(d);
    r8.move(d);

    changeVertices();
    updateVertices();
}

void cylinder::rotate(float* otherMid,float angle)
{
    float center[3];
    calcMidPoint(center);
    float Q[3];
    Q[0] = otherMid[0] - center[0];
    Q[1] = otherMid[1] - center[1];
    Q[2] = otherMid[2] - center[2];
    //normalise
    float lengthQ = sqrt((Q[0]*Q[0])+(Q[1]*Q[1])+(Q[2]*Q[2]));
    float normalQ[3];
    normalQ[0] = (1/lengthQ) * Q[0];
    normalQ[1] = (1/lengthQ) * Q[1];
    normalQ[2] = (1/lengthQ) * Q[2];

    IdentityMatrix<4> Origin;
    Origin[0][3] = center[0];
    Origin[1][3] = center[1];
    Origin[2][3] = center[2];

    IdentityMatrix<4> T;
    T[0][3] = -1*center[0];
    T[1][3] = -1*center[1];
    T[2][3] = -1*center[2];


    float d = sqrt((normalQ[1]*normalQ[1])+(normalQ[2]*normalQ[2]));
    if (d==0)
    {
        std::cout << "d=0";
        return;
    }
    Q[0] = normalQ[0];
    Q[1] = normalQ[1];
    Q[2] = normalQ[2];
    IdentityMatrix<4> Rx;
    Rx[1][1] = Q[2] / d;
    Rx[1][2] = (-1*Q[1]) / d;
    Rx[2][1] = Q[1] / d;
    Rx[2][2] = Q[2] / d;
    IdentityMatrix<4> nRx;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
                nRx[j][i] = Rx[i][j];
        }
    }
    /*Rx[1][1] = Q[2] / d;
    Rx[1][2] = (Q[1]) / d;
    Rx[2][1] = (-1*Q[1]) / d;
    Rx[2][2] = Q[2] / d;*/

    IdentityMatrix<4> Ry;
    Ry[0][0] = d;
    Ry[0][2] = -1*Q[0];
    Ry[2][0] = Q[0];
    Ry[2][2] = d;
    IdentityMatrix<4> nRy;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
                nRy[j][i] = Ry[i][j];
        }
    }
    /*Ry[0][0] = d;
    Ry[0][2] = Q[0];
    Ry[2][0] = -1*Q[0];
    Ry[2][2] = d;*/

    //float angle = 0.1;
    IdentityMatrix<4> Rz;
    Rz[0][0]= cos(angle);
    Rz[0][1]= -1*sin(angle);
    Rz[1][0]= sin(angle);
    Rz[1][1]= cos(angle);
    Rz[2][2] = 1;
    Rz[3][3]=1;

    Matrix<4,4> rotationM;
    //R = T(P0)Rx (−θx )Ry (−θy )Rz (θ)Ry (θy )Rx (θx )T(−P0)
    rotationM = Origin*nRx*nRy *Rz* Ry*Rx*T;
    //Origin = T(P0)

    //mulitply rotationM with each vertex in shape
    multiplyMcircle(rotationM,top.vertices);
    multiplyMcircle(rotationM,bottom.vertices);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);
    multiplyM(rotationM,r4.tri1);
    multiplyM(rotationM,r4.tri2);
    multiplyM(rotationM,r5.tri1);
    multiplyM(rotationM,r5.tri2);
    multiplyM(rotationM,r6.tri1);
    multiplyM(rotationM,r6.tri2);
    multiplyM(rotationM,r7.tri1);
    multiplyM(rotationM,r7.tri2);
    multiplyM(rotationM,r8.tri1);
    multiplyM(rotationM,r8.tri2);

    updateVertices();
}
