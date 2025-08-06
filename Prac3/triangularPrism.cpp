#include "shapes3D.h"

triangularPrism::triangularPrism()
{
    float mid[3];
    mid[0] = -0.1;
    mid[1] = 0.03;
    mid[2] = 0;
    width =0.4;
    degree = 0.1;
    height = 0.3;

    setWidth(width);
    setHeight(height);

    changeVertices();
    updateVertices();

    setColour("red");
}

void triangularPrism::changeVertices()
{

    for (int i=0;i<9;i+=3)
    {
        r1.tri1[i] = front.vertex[i];
        r1.tri1[i+1] = front.vertex[i+1];
        r1.tri1[i+2] = front.vertex[i+2];
        r1.tri2[i] = back.vertex[i];
        r1.tri2[i+1] = back.vertex[i+1];
        r1.tri2[i+2] = back.vertex[i+2];

        r2.tri1[i] = front.vertex[i+3];
        r2.tri1[i+1] = front.vertex[i+3+1];
        r2.tri1[i+2] = front.vertex[i+3+2];
        r2.tri2[i] = back.vertex[i+3];
        r2.tri2[i+1] = back.vertex[i+3+1];
        r2.tri2[i+2] = back.vertex[i+3+2];

        if ((i+6)>9)
        {
            r3.tri1[i] =front.vertex[i];
            r3.tri1[i+1] = front.vertex[i+1];
            r3.tri1[i+2] = front.vertex[i+2];
            r3.tri2[i] = back.vertex[i];
            r3.tri2[i+1] = back.vertex[i+1];
            r3.tri2[i+2] = back.vertex[i+2];
        }else{
            r3.tri1[i] =front.vertex[i+6];
            r3.tri1[i+1] = front.vertex[i+6+1];
            r3.tri1[i+2] = front.vertex[i+6+2];
            r3.tri2[i] = back.vertex[i+6];
            r3.tri2[i+1] = back.vertex[i+6+1];
            r3.tri2[i+2] = back.vertex[i+6+2];
        }
    }
    for (int i=6;i<9;i+=3)
    {
        r1.tri1[i] = back.vertex[i-3];
        r1.tri1[i+1] = back.vertex[i-3+1];
        r1.tri1[i+2] = back.vertex[i-3+2];
        r1.tri2[i] = front.vertex[i-6];
        r1.tri2[i+1] = front.vertex[i-6+1];
        r1.tri2[i+2] = front.vertex[i-6+2];

        r2.tri1[i] = back.vertex[i];
        r2.tri1[i+1] = back.vertex[i+1];
        r2.tri1[i+2] = back.vertex[i+2];
        r2.tri2[i] = front.vertex[i-3];
        r2.tri2[i+1] = front.vertex[i-3+1];
        r2.tri2[i+2] = front.vertex[i-3+2];

        r3.tri1[0] = back.vertex[i];
        r3.tri1[0+1] = back.vertex[i+1];
        r3.tri1[0+2] = back.vertex[i+2];
        r3.tri2[6] = front.vertex[i];
        r3.tri2[6+1] = front.vertex[i+1];
        r3.tri2[6+2] = front.vertex[i+2];
    }
    r3.tri1[3] = r1.tri1[0];
    r3.tri1[4] =  r1.tri1[1];
    r3.tri1[5] = r1.tri1[2];
    r3.tri2[3] = back.vertex[0];
    r3.tri2[4] =  back.vertex[1];
    r3.tri2[5] = back.vertex[2];
    r3.tri2[6] = front.vertex[0];
    r3.tri2[7] =  front.vertex[1];
    r3.tri2[8] = front.vertex[2];
}

void triangularPrism::updateVertices()
{
    for (int i=0;i<9;i++)
    {
       vertices[i] = front.vertex[i];
       vertices[i+9] = back.vertex[i];
       vertices[i+18] = r1.tri1[i];
       vertices[i+27] = r1.tri2[i];
       vertices[i+36] = r2.tri1[i];
       vertices[i+45] = r2.tri2[i];
       vertices[i+54] = r3.tri1[i];
       vertices[i+63] = r3.tri2[i];
    }
}

void triangularPrism::setColour(std::string col)
{
    front.setColour(col);
            back.setColour(col);
            r1.setColour(col);
            r2.setColour(col);
            r3.setColour(col);

    for (int i=0;i<9;i++)
    {
        colours[i] = front.col[i];
        colours[i+9] = back.col[i];
    }
    for (int i=0;i<18;i++)
    {
        colours[i+18] = r1.col[i];
        colours[i+36] = r2.col[i];
        colours[i+54] = r3.col[i];
    }
}

void triangularPrism::setWidth(float width) //x-val
{
    this->width = width;
    float w = width/2;
    float midpoint[3];

    //front.calcMidPoint(midpoint);
    float m = (front.vertex[6] + front.vertex[3])/2;
        front.vertex[0] = m - w;
        front.vertex[3] = m + w;
        front.vertex[6] = m;
        m = (back.vertex[6] + back.vertex[3])/2;
        back.vertex[0] = m - w;
        back.vertex[3] = m + w;
        back.vertex[6] = m;

    changeVertices();
    updateVertices();

}
void triangularPrism::setHeight(float h)//z-val
{
    this->height = h;
    for (int i=2;i<9;i+=3)
    {
        back.vertex[i] = front.vertex[i];
        back.vertex[i] -= height;
    }
    changeVertices();
    updateVertices();
}

void triangularPrism::setDegree(float d)
{
    degree=d;
}

void triangularPrism::setMidPoint(float* mid)
{
    float z = mid[2];
    float r = width/2;
    mid[2] = z+r;

    //front.setMidPoint(mid);
    mid[2] = z-r;
    //back.setMidPoint(mid);
    changeVertices();
    updateVertices();
}

void triangularPrism::calcMidPoint(float* coordinates)
{
    int x=0; int y=1;int z=2;
    coordinates[x]=0;
    coordinates[y]=0;
    coordinates[z]=0;

        coordinates[x] = front.vertex[0] + back.vertex[0];
        coordinates[y] = front.vertex[1]+ back.vertex[1];
        coordinates[z] = front.vertex[2] +back.vertex[2];
  
    coordinates[x] /= 2;
    coordinates[y] /= 2;
    coordinates[z] /= 2;
}

void triangularPrism::rotateLeftX(float* mid)
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
    multiplyM(rotationM,front.vertex);
    multiplyM(rotationM,back.vertex);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);

    updateVertices();
}
void triangularPrism::rotateRightX(float* mid)
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
    multiplyM(rotationM,front.vertex);
    multiplyM(rotationM,back.vertex);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);

    updateVertices();
}
void triangularPrism::rotateLeftY(float* mid)
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
   // rotationM = T*R*Origin;
    //mulitply rotationM with each vertex in shape
    multiplyM(rotationM,front.vertex);
    multiplyM(rotationM,back.vertex);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);

    updateVertices();
}
void triangularPrism::rotateRightY(float* mid)
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
    //rotationM = T*R*Origin;

    //mulitply rotationM with each vertex in shape
    multiplyM(rotationM,front.vertex);
    multiplyM(rotationM,back.vertex);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);

    updateVertices();
}

void triangularPrism::rotateLeftZ(float* mid)
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
    multiplyM(rotationM,front.vertex);
    multiplyM(rotationM,back.vertex);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);

    updateVertices();
}

void triangularPrism::rotateRightZ(float* mid)
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
    multiplyM(rotationM,front.vertex);
    multiplyM(rotationM,back.vertex);
    multiplyM(rotationM,r1.tri1);
    multiplyM(rotationM,r1.tri2);
    multiplyM(rotationM,r2.tri1);
    multiplyM(rotationM,r2.tri2);
    multiplyM(rotationM,r3.tri1);
    multiplyM(rotationM,r3.tri2);

    updateVertices();
}

void triangularPrism::move(std::string d)
{
    front.move(d,0.01);
    back.move(d,0.01);
    r1.move(d);
    r2.move(d);
    r3.move(d);

    updateVertices();
}

void triangularPrism::move(std::string d,float n)
{
    front.move(d,n);
    back.move(d,n);
    r1.move(d);
    r2.move(d);
    r3.move(d);

    changeVertices();
    updateVertices();
}

