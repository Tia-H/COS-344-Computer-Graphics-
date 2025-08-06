#include "shapes3D.h"
#include "shapes.cpp"
#include "colour.h"
#include "Matrix.cpp"

void multiplyM(Matrix<4,4> r,float* tri)
        {
            Matrix<4,1> v1;
            v1[0][0]=tri[0];    v1[1][0]=tri[1];    v1[2][0]=tri[2];    v1[3][0]=1;
            Matrix<4,1> v2;
            v2[0][0]=tri[3];    v2[1][0]=tri[4];    v2[2][0]=tri[5];    v2[3][0]=1;
            Matrix<4,1> v3;
            v3[0][0]=tri[6];    v3[1][0]=tri[7];    v3[2][0]=tri[8];    v3[3][0]=1;
            
            Matrix<4,1> final;
            final = r*v1;
            final[3][0] = 1;
            tri[0] = final[0][0];    tri[1] = final[1][0];    tri[2] = final[2][0];
            for (int i=0;i<3;i++)
            {
               // tri[i] /=final[3][0];
            
            }
            
            final = r*v2;
            final[3][0] = 1;
            tri[3] = final[0][0];    tri[4] = final[1][0];    tri[5] = final[2][0];
            for (int i=3;i<6;i++)
            {
                //tri[i] /=final[3][0];
            }
            final = r*v3;
            final[3][0] = 1;
            tri[6] = final[0][0];    tri[7] = final[1][0];    tri[8] = final[2][0];
            for (int i=6;i<9;i++)
            {
                //tri[i] /=final[3][0];
            }

        }
cuboid::cuboid()
{
    degree = 0.1;
    //y-values
    front.tri1[1] = 0.03;
    front.tri1[4] = 0.03;
    front.tri1[7] = 0;
    front.tri2[1] = 0.03;
    front.tri2[4] = 0;
    front.tri2[7] = 0;
    back.tri1[1] = 0.03;
    back.tri1[4] = 0.03;
    back.tri1[7] = 0;
    back.tri2[1] = 0.03;
    back.tri2[4] = 0;
    back.tri2[7] = 0;
    //z-axis for front and back
    front.tri1[2] = -0.6; 
    front.tri1[5] = -0.6; 
    front.tri1[8] = -0.6; 
    front.tri2[2] = -0.6; 
    front.tri2[5] = -0.6; 
    front.tri2[8] = -0.6; 
    back.tri1[2] = 0.4; 
    back.tri1[5] = 0.4;
    back.tri1[8] = 0.4;
    back.tri2[2] = 0.4; 
    back.tri2[5] = 0.4;
    back.tri2[8] = 0.4;
    
    //set top and bottom
    changeVertices();
    updateVertices();

    height = abs(front.tri1[1] - front.tri1[7]);
    width = abs(front.tri1[0] - front.tri1[3]);
    length = abs(top.tri1[2] - top.tri1[8]);
}

void cuboid::setColour(std::string col,float a)
{
        front.setColour(col,a);
            back.setColour(col,a);
            top.setColour(col,a);
            bottom.setColour(col,a);
            rSide.setColour(col,a);
            lSide.setColour(col,a);

    OriginalCol[0] = front.col[0];OriginalCol[1] = front.col[1];OriginalCol[2] = front.col[2];
    updateCol();
}

void cuboid::updateCol()
{
    /*for (int i=0;i<9;i++)
    {
        colours[i]= front.col[i];
        colours[i+9]= front.col[i+9];
        colours[i+18]= back.col[i];
        colours[i+27]= back.col[i+9];
        colours[i+36]= top.col[i];
        colours[i+45]= top.col[i+9];
        colours[i+54]= bottom.col[i];
        colours[i+63]= bottom.col[i+9];
        colours[i+72]= lSide.col[i];
        colours[i+81]= lSide.col[i+9];
        colours[i+90]= rSide.col[i];
        colours[i+99]= rSide.col[i+9];

    }*/
    for (int i=0;i<24;i++)
    {
        colours[i]= front.col[i];
        colours[i+24]= back.col[i];
        colours[i+48]= top.col[i];
        colours[i+72]= bottom.col[i];
        colours[i+96]= lSide.col[i];
        colours[i+120]= rSide.col[i];
    }
}

void cuboid::calcMidPoint(float* coordinates)
{
    int x=0; int y=1;int z=2;
    coordinates[x]=0;
    coordinates[y]=0;
    coordinates[z]=0;
        /*coordinates[x] = front.tri1[0] + back.tri1[3];
        coordinates[y] = front.tri1[0+y] +back.tri1[4];
        coordinates[z] = front.tri1[0+z] +back.tri1[5];*/
        coordinates[x] = front.tri1[0] + back.tri2[3];
        coordinates[y] = front.tri1[0+y] +back.tri2[4];
        coordinates[z] = front.tri1[0+z] +back.tri2[5];
  
    coordinates[x] /= 2;
    coordinates[y] /= 2;
    coordinates[z] /= 2;
}


void cuboid::rotateLeftX(float* mid)
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
    multiplyM(rotationM,front.tri1);
    multiplyM(rotationM,front.tri2);
    multiplyM(rotationM,back.tri1);
    multiplyM(rotationM,back.tri2);
    multiplyM(rotationM,top.tri1);
    multiplyM(rotationM,top.tri2);
    multiplyM(rotationM,bottom.tri1);
    multiplyM(rotationM,bottom.tri2);
    multiplyM(rotationM,lSide.tri1);
    multiplyM(rotationM,lSide.tri2);
    multiplyM(rotationM,rSide.tri1);
    multiplyM(rotationM,rSide.tri2);

    //changeVertices();
    updateVertices();
}
void cuboid::rotateRightX(float* mid)
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
    multiplyM(rotationM,front.tri1);
    multiplyM(rotationM,front.tri2);
    multiplyM(rotationM,back.tri1);
    multiplyM(rotationM,back.tri2);
    multiplyM(rotationM,top.tri1);
    multiplyM(rotationM,top.tri2);
    multiplyM(rotationM,bottom.tri1);
    multiplyM(rotationM,bottom.tri2);
    multiplyM(rotationM,lSide.tri1);
    multiplyM(rotationM,lSide.tri2);
    multiplyM(rotationM,rSide.tri1);
    multiplyM(rotationM,rSide.tri2);

    //changeVertices();
    updateVertices();
}
void cuboid::rotateLeftY(float* mid)
{
    float angle=degree;
    float coords[3];
   // calcMidPoint(coords);
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
    multiplyM(rotationM,front.tri1);
    multiplyM(rotationM,front.tri2);
    multiplyM(rotationM,back.tri1);
    multiplyM(rotationM,back.tri2);
    multiplyM(rotationM,top.tri1);
    multiplyM(rotationM,top.tri2);
    multiplyM(rotationM,bottom.tri1);
    multiplyM(rotationM,bottom.tri2);
    multiplyM(rotationM,lSide.tri1);
    multiplyM(rotationM,lSide.tri2);
    multiplyM(rotationM,rSide.tri1);
    multiplyM(rotationM,rSide.tri2);

    //changeVertices();
    updateVertices();
}
void cuboid::rotateRightY(float* mid)
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
    multiplyM(rotationM,front.tri1);
    multiplyM(rotationM,front.tri2);
    multiplyM(rotationM,back.tri1);
    multiplyM(rotationM,back.tri2);
    multiplyM(rotationM,top.tri1);
    multiplyM(rotationM,top.tri2);
    multiplyM(rotationM,bottom.tri1);
    multiplyM(rotationM,bottom.tri2);
    multiplyM(rotationM,lSide.tri1);
    multiplyM(rotationM,lSide.tri2);
    multiplyM(rotationM,rSide.tri1);
    multiplyM(rotationM,rSide.tri2);

    //changeVertices();
    updateVertices();
}

void cuboid::rotateLeftZ(float* mid)
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
    R[2][2] = 1;
    R[3][3]=1;

    Matrix<4,4> rotationM;
    rotationM = Origin*R*T;

    //mulitply rotationM with each vertex in shape
    multiplyM(rotationM,front.tri1);
    multiplyM(rotationM,front.tri2);
    multiplyM(rotationM,back.tri1);
    multiplyM(rotationM,back.tri2);
    multiplyM(rotationM,top.tri1);
    multiplyM(rotationM,top.tri2);
    multiplyM(rotationM,bottom.tri1);
    multiplyM(rotationM,bottom.tri2);
    multiplyM(rotationM,lSide.tri1);
    multiplyM(rotationM,lSide.tri2);
    multiplyM(rotationM,rSide.tri1);
    multiplyM(rotationM,rSide.tri2);

    //changeVertices();
    updateVertices();
}

void cuboid::rotateRightZ(float* mid)
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
    multiplyM(rotationM,front.tri1);
    multiplyM(rotationM,front.tri2);
    multiplyM(rotationM,back.tri1);
    multiplyM(rotationM,back.tri2);
    multiplyM(rotationM,top.tri1);
    multiplyM(rotationM,top.tri2);
    multiplyM(rotationM,bottom.tri1);
    multiplyM(rotationM,bottom.tri2);
    multiplyM(rotationM,lSide.tri1);
    multiplyM(rotationM,lSide.tri2);
    multiplyM(rotationM,rSide.tri1);
    multiplyM(rotationM,rSide.tri2);

    //changeVertices();
    updateVertices();
}

void cuboid::move(std::string d)
{
    front.move(d);
    back.move(d);
    top.move(d);
    bottom.move(d);
    lSide.move(d);
    rSide.move(d);

    //changeVertices();
    updateVertices();
}

void cuboid::move(std::string d,float n)
{
    front.move(d,n);
    back.move(d,n);
    top.move(d,n);
    bottom.move(d,n);
    lSide.move(d,n);
    rSide.move(d,n);

    //changeVertices();
    updateVertices();
}

void cuboid::setHeight(float h) //change y value
{
    float mid[3];
    calcMidPoint(mid);
    this-> height = h;

    float r = h/2;
    front.tri1[1] = mid[1] + r;
    front.tri1[4] = mid[1] + r;
    front.tri1[7] =  mid[1] - r;
    front.tri2[1] =mid[1] + r;
    front.tri2[4] =  mid[1] - r;
    front.tri2[7] =  mid[1] - r;
    back.tri1[1] =mid[1] + r;
    back.tri1[4] = mid[1] + r;
    back.tri1[7] =  mid[1] - r;
    back.tri2[1] = mid[1] + r;
    back.tri2[4] =  mid[1] - r;
    back.tri2[7] =  mid[1] - r;
    
    changeVertices();
    updateVertices();
}

void cuboid::setWidth(float w) //change x values
{
    float mid[3];
    calcMidPoint(mid);
    this->width =w;

    float r = w/2;

    front.tri1[0] = mid[0] - r ;
    front.tri1[3] = mid[0] + r;
    front.tri1[6] = mid[0] - r;
    front.tri2[0] = mid[0] + r;
    front.tri2[3] = mid[0] + r;
    front.tri2[6] = mid[0] - r;
    back.tri1[0] = mid[0] - r;
    back.tri1[3] = mid[0] + r;
    back.tri1[6] = mid[0] - r;
    back.tri2[0] = mid[0] + r;
    back.tri2[3] = mid[0] + r;
    back.tri2[6] = mid[0] - r;
    
    changeVertices();
    updateVertices();
}

void cuboid::makeTrapezoid()
{
    float mid[3];
    calcMidPoint(mid);

    float r = width/4;

    front.tri1[0] = mid[0] - r ;
    front.tri1[3] = mid[0] + r;
    front.tri1[6] = mid[0] - r;
    front.tri2[0] = mid[0] + r;
    front.tri2[3] = mid[0] + r;
    front.tri2[6] = mid[0] - r;


    changeVertices();
    updateVertices();
}

void cuboid::makeLTrapezoid()
{
    float mid[3];
    calcMidPoint(mid);

    float r = width/4;
    front.tri1[0] = mid[0] - r ;
    //front.tri1[3] = mid[0] + r;
    front.tri1[6] = mid[0] - r;
    //front.tri2[0] = mid[0] + r;
    //front.tri2[3] = mid[0] + r;
    front.tri2[6] = mid[0] - r;

    changeVertices();
    updateVertices();
}
void cuboid::makeRTrapezoid()
{
    float mid[3];
    calcMidPoint(mid);

    float r = width/4;
    //front.tri1[0] = mid[0] - r ;
    front.tri1[3] = mid[0] + r;
    //front.tri1[6] = mid[0] - r;
    front.tri2[0] = mid[0] + r;
    front.tri2[3] = mid[0] + r;
    //front.tri2[6] = mid[0] - r;

    changeVertices();
    updateVertices();
}

void cuboid::setLength(float l) //chnage z values
{
    float mid[3];
    calcMidPoint(mid);
    length = l;

    float r = l/2;
    for (int i=0;i<9;i+=3)
    {
        front.tri1[i+2] = mid[2] + r;
        front.tri2[i+2] = mid[2] + r;
        back.tri1[i+2] = mid[2] - r;
        back.tri2[i+2] = mid[2] - r;
    }

    changeVertices();
    updateVertices();
}


void cuboid::changeVertices()
{
    
    //set top and bottom
    top.tri1[0] = back.tri1[0];     top.tri1[1] = back.tri1[1];     top.tri1[2] = back.tri1[2];
    top.tri1[3] = back.tri1[3];     top.tri1[4] = back.tri1[4];     top.tri1[5] = back.tri1[5];
    top.tri1[6] = front.tri1[0];     top.tri1[7] = front.tri1[1];    top.tri1[8] = front.tri1[2];
    top.tri2[0] = back.tri1[3];     top.tri2[1] = back.tri1[4];     top.tri2[2] = back.tri1[5];
    top.tri2[3] = front.tri1[3];    top.tri2[4] = front.tri1[4];    top.tri2[5] = front.tri1[5];
    top.tri2[6] = front.tri1[0];    top.tri2[7] = front.tri1[1];    top.tri2[8] = front.tri1[2];
    
    for (int i=0;i<9;i++)
    {
        bottom.tri1[i] = top.tri1[i];
        bottom.tri2[i] = top.tri2[i];
    }
    bottom.tri1[1] = back.tri1[7]; 
    bottom.tri1[4] = back.tri2[4];
    bottom.tri1[7] = front.tri2[4];
    bottom.tri2[1] = back.tri2[4];
    bottom.tri2[4] = front.tri2[4];
    bottom.tri2[7] = front.tri2[7];

    //left+right sides
    lSide.tri1[0] = back.tri1[6]; lSide.tri1[1] = back.tri1[7]; lSide.tri1[2] = back.tri1[8];
    lSide.tri1[3] = back.tri1[0]; lSide.tri1[4] = back.tri1[1]; lSide.tri1[5] = back.tri1[2];
    lSide.tri1[6] = front.tri1[0]; lSide.tri1[7] = front.tri1[1]; lSide.tri1[8] = front.tri1[2];
    lSide.tri2[0] = back.tri1[6]; lSide.tri2[1] = back.tri1[7]; lSide.tri2[2] = back.tri1[8];
    lSide.tri2[3] = front.tri1[6]; lSide.tri2[4] = front.tri1[7]; lSide.tri2[5] = front.tri1[8];
    lSide.tri2[6] = front.tri1[0]; lSide.tri2[7] = front.tri1[1]; lSide.tri2[8] = front.tri1[2];

    for (int i=0;i<9;i++)
    {
        rSide.tri1[i] = lSide.tri1[i];
        rSide.tri2[i] = lSide.tri2[i];
    }
    rSide.tri1[0] = back.tri2[3];
    rSide.tri1[3] = back.tri1[3];
    rSide.tri1[6] = front.tri1[3];
    rSide.tri2[0] = back.tri2[3];
    rSide.tri2[3] = front.tri2[3];
    rSide.tri2[6] = front.tri1[3];
}

void cuboid::updateVertices()
{
    for (int i=0;i<9;i++)
    {
        vertices[i]= front.tri1[i];
        vertices[i+9]= front.tri2[i];
        vertices[i+18]= back.tri1[i];
        vertices[i+27]= back.tri2[i];
        vertices[i+36]= top.tri1[i];
        vertices[i+45]= top.tri2[i];
        vertices[i+54]= bottom.tri1[i];
        vertices[i+63]= bottom.tri2[i];
        vertices[i+72]= lSide.tri1[i];
        vertices[i+81]= lSide.tri2[i];
        vertices[i+90]= rSide.tri1[i];
        vertices[i+99]= rSide.tri2[i];

    }
}

void cuboid::rotate(float* otherMid)
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

    float angle = 0.1;
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
    multiplyM(rotationM,front.tri1);
    multiplyM(rotationM,front.tri2);
    multiplyM(rotationM,back.tri1);
    multiplyM(rotationM,back.tri2);
    multiplyM(rotationM,top.tri1);
    multiplyM(rotationM,top.tri2);
    multiplyM(rotationM,bottom.tri1);
    multiplyM(rotationM,bottom.tri2);
    multiplyM(rotationM,lSide.tri1);
    multiplyM(rotationM,lSide.tri2);
    multiplyM(rotationM,rSide.tri1);
    multiplyM(rotationM,rSide.tri2);

    updateVertices();
}


void cuboid::calFaceNormal(float* p1,float* p2,float* p3,float* res)
{
    float edge[3];
    edge[0] = p2[0] - p1[0];edge[1] = p2[1] - p1[1];edge[2] = p2[2] - p1[2];
    float edge2[3];
    edge2[0] = p3[0] - p1[0];edge2[1] = p3[1] - p1[1];edge2[2] = p3[2] - p1[2];

    //cross product
    float a[3];
    a[0] = (edge[1]*edge2[2]) - (edge[2]*edge2[1]); //u2v3-u3v2
    a[1] = (edge[2]*edge2[0]) - (edge[0]*edge2[2]); //u3v1-u1v3
    a[2] = (edge[0]*edge2[1]) - (edge[1]*edge2[0]); //u1v2-u2v1

    //normalise
    float l = sqrt((a[0]*a[0]) + (a[1]*a[1]) + (a[2]*a[2]));
    res[0] = a[0]/l;
    res[1] = a[1]/l;
    res[2] = a[2]/l;
}
void cuboid::calNormal()
{
    float fNorms[3];
    float tri1[3]; 
    tri1[0] = front.tri1[0];tri1[1] = front.tri1[1];tri1[2] = front.tri1[2];
    float tri2[3]; 
    tri2[0] = front.tri1[3];tri2[1] = front.tri1[4];tri2[2] = front.tri1[5];
    float tri3[3]; 
    tri3[0] = front.tri1[6];tri3[1] = front.tri1[7];tri3[2] = front.tri1[8];
    calFaceNormal(tri1,tri2,tri3,fNorms);
    for (int i=0;i<9;i+=3)
    {
        normals[i] = fNorms[0];
        normals[i+1] = fNorms[1];
        normals[i+2] = fNorms[2];

        normals[i+18] = -fNorms[0];
        normals[i+1+18] = -fNorms[1];
        normals[i+2+18] = -fNorms[2];
    }

    tri1[0] = front.tri2[0];tri1[1] = front.tri2[1];tri1[2] = front.tri2[2];
    tri2[0] = front.tri2[3];tri2[1] = front.tri2[4];tri2[2] = front.tri2[5];
    tri3[0] = front.tri2[6];tri3[1] = front.tri2[7];tri3[2] = front.tri2[8];
    calFaceNormal(tri1,tri2,tri3,fNorms);
    for (int i=0;i<9;i+=3)
    {
        normals[i+9] = fNorms[0];
        normals[i+1+9] = fNorms[1];
        normals[i+2+9] = fNorms[2];

        normals[i+27] = -fNorms[0];
        normals[i+1+27] = -fNorms[1];
        normals[i+2+27] = -fNorms[2];
    }

    tri1[0] = top.tri1[0];tri1[1] = top.tri1[1];tri1[2] = top.tri1[2];
    tri2[0] = top.tri1[3];tri2[1] = top.tri1[4];tri2[2] = top.tri1[5];
    tri3[0] = top.tri1[6];tri3[1] = top.tri1[7];tri3[2] = top.tri1[8];
    calFaceNormal(tri1,tri2,tri3,fNorms);
    for (int i=0;i<9;i+=3)
    {
        normals[i+36] = fNorms[0];
        normals[i+1+36] = fNorms[1];
        normals[i+2+36] = fNorms[2];

        normals[i+54] = -fNorms[0];
        normals[i+1+54] = -fNorms[1];
        normals[i+2+54] = -fNorms[2];
    }

    tri1[0] = top.tri2[0];tri1[1] = top.tri2[1];tri1[2] = top.tri2[2];
    tri2[0] = top.tri2[3];tri2[1] = top.tri2[4];tri2[2] = top.tri2[5];
    tri3[0] = top.tri2[6];tri3[1] = top.tri2[7];tri3[2] = top.tri2[8];
    calFaceNormal(tri1,tri2,tri3,fNorms);
    for (int i=0;i<9;i+=3)
    {
        normals[i+45] = fNorms[0];
        normals[i+1+45] = fNorms[1];
        normals[i+2+45] = fNorms[2];

        normals[i+63] = -fNorms[0];
        normals[i+1+63] = -fNorms[1];
        normals[i+2+63] = -fNorms[2];
    }

    tri1[0] = lSide.tri1[0];tri1[1] = lSide.tri1[1];tri1[2] = lSide.tri1[2];
    tri2[0] = lSide.tri1[3];tri2[1] = lSide.tri1[4];tri2[2] = lSide.tri1[5];
    tri3[0] = lSide.tri1[6];tri3[1] = lSide.tri1[7];tri3[2] = lSide.tri1[8];
    calFaceNormal(tri1,tri2,tri3,fNorms);
    for (int i=0;i<9;i+=3)
    {
        normals[i+72] = -fNorms[0];
        normals[i+1+72] = -fNorms[1];
        normals[i+2+72] = -fNorms[2];

        normals[i+90] = fNorms[0];
        normals[i+1+90] = fNorms[1];
        normals[i+2+90] = fNorms[2];
    }

    tri1[0] = lSide.tri2[0];tri1[1] = lSide.tri2[1];tri1[2] = lSide.tri2[2];
    tri2[0] = lSide.tri2[3];tri2[1] = lSide.tri2[4];tri2[2] = lSide.tri2[5];
    tri3[0] = lSide.tri2[6];tri3[1] = lSide.tri2[7];tri3[2] = lSide.tri2[8];
    calFaceNormal(tri1,tri2,tri3,fNorms);
    for (int i=0;i<9;i+=3)
    {
        normals[i+81] = fNorms[0];
        normals[i+1+81] = fNorms[1];
        normals[i+2+81] = fNorms[2];

        normals[i+99] = -fNorms[0];
        normals[i+1+99] = -fNorms[1];
        normals[i+2+99] = -fNorms[2];
    }
}

void cuboid::pointLight(cuboid* c)
{
    float colour[3]; //i
        colour[0] = OriginalCol[0];colour[1] = OriginalCol[1];colour[2] = OriginalCol[2];

        float pointP[3]; //p
        calcMidPoint(pointP);
    int colIndex=0;
    for (int i=0;i<108;i+=3)// for each pixel do
    {
        //calculate where ray intersects surface = x[3]
        float x[3];//pixel
        x[0] = c->vertices[i];x[1] = c->vertices[i+1];x[2] = c->vertices[i+2];
        
        //r = p-x
        float r[3]; //lightDirection
        r[0] = pointP[0]-x[0]; r[1] = pointP[1]-x[1]; r[2] = pointP[2]-x[2];
        float rLength = sqrt((r[0]*r[0]) + (r[1]*r[1]) + (r[2]*r[2]));
        float l[3];
        l[0] = r[0] / rLength; //normalise lightDirection
        l[1] = r[1] / rLength; 
        l[2] = r[2] / rLength; 
        //calculate normal at x
        float n[3];
        n[0] = c->normals[i];n[1] = c->normals[i+1];n[2]  = c->normals[i+2];

        float E[3];
        float max=0;
        float dotProduct=0;
        for (int i=0; i<3; i++)
        {
            dotProduct += (n[i]*l[i]);
        }
        if (dotProduct<0)
        {
            max=0;
        }else{
            max = dotProduct;
        }
        E[0] = (max * colour[0])/ (rLength*rLength);
        E[1] = (max * colour[1])/ (rLength*rLength);
        E[2] = (max * colour[2])/ (rLength*rLength);

        //calculate resulting colour
        float k[3];
        //k[0] = c->colours[colIndex];k[1] = c->colours[colIndex+1]; k[2] = c->colours[colIndex+2];
        k[0] = c->OriginalCol[0];k[1] = c->OriginalCol[1]; k[2] = c->OriginalCol[2];

        float final[3];
        final[0] = k[0]*E[0];
        final[1] = k[1]*E[1];
        final[2] = k[2]*E[2];

        c->colours[colIndex] = final[0];
        c->colours[colIndex+1] =final[1];
        c->colours[colIndex+2] =final[2];
        colIndex+=4;
    }

    //return final;
}

void cuboid::setRectangles(int r)
{
    float t = (width*height)/r;
    float w = width/2;
    float h = t/w;
    /*float w = width/r;
    float h = height/r;*/
    cuboid newRec;
    newRec.setHeight(h);
    newRec.setWidth(w);
    newRec.setLength(length);
    for (int i=0; i<r;i++)
    {
        for (int j=0;j<2;j++)
        {

        }
    }


}

void cuboid::moveUp(cuboid* c)
{
    float axis[3];
    c->calcMidPoint(axis);
    for (int i=1;i<vSize;i+=3)
    {
        
    }
}