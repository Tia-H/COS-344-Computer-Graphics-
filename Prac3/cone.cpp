#include "shapes3D.h"

cone::cone()
{
    setColour("yellow");
    int x=0; int y=1; int z=2;
    float mid[3];
    mid[0] = -0.1;
    mid[1] = 0.03;
    mid[2] = 0;

    //set base
    for (int i=0;i<30;i+=3)
    {
        base.vertices[i+z] = base.vertices[i];
        base.vertices[i] = 0;
    }
    setMidPoint(mid);
    
    for (int i=0;i<9;i+=3)
    {
        t1.vertex[i] = base.vertices[i+3];
        t1.vertex[i+1] = base.vertices[i+1+3];
        t1.vertex[i+2] = base.vertices[i+2+3];
        t2.vertex[i] = base.vertices[i+6];
        t2.vertex[i+1] = base.vertices[i+1+6];
        t2.vertex[i+2] = base.vertices[i+2+6];
        t3.vertex[i] = base.vertices[i+9];
        t3.vertex[i+1] = base.vertices[i+1+9];
        t3.vertex[i+2] = base.vertices[i+2+9];
        t4.vertex[i] = base.vertices[i+12];
        t4.vertex[i+1] = base.vertices[i+1+12];
        t4.vertex[i+2] = base.vertices[i+2+12];
        t5.vertex[i] = base.vertices[i+15];
        t5.vertex[i+1] = base.vertices[i+1+15];
        t5.vertex[i+2] = base.vertices[i+2+15];
        t6.vertex[i] = base.vertices[i+18];
        t6.vertex[i+1] = base.vertices[i+1+18];
        t6.vertex[i+2] = base.vertices[i+2+18];
        t7.vertex[i] = base.vertices[i+21];
        t7.vertex[i+1] = base.vertices[i+1+21];
        t7.vertex[i+2] = base.vertices[i+2+21];
        t8.vertex[i] = base.vertices[i+24];
        t8.vertex[i+1] = base.vertices[i+1+24];
        t8.vertex[i+2] = base.vertices[i+2+24];
        if (i==6)
        {
            mid[1] = base.vertices[1]+0.07;
            t1.vertex[i] = mid[0] * -8;
            t1.vertex[i+1] = mid[1];//base.vertices[i+4];
            t1.vertex[i+2] = mid[2];//base.vertices[i+5];
            t2.vertex[i] = mid[0] * -8;
            t2.vertex[i+1] = mid[1];//base.vertices[i+4];
            t2.vertex[i+2] = mid[2];//base.vertices[i+5];
            t3.vertex[i] = mid[0] * -8;
            t3.vertex[i+1] = mid[1];//base.vertices[i+4];
            t3.vertex[i+2] = mid[2];//base.vertices[i+5];
            t4.vertex[i] = mid[0] * -8;
            t4.vertex[i+1] = mid[1];//base.vertices[i+4];
            t4.vertex[i+2] = mid[2];//base.vertices[i+5];
            t5.vertex[i] = mid[0] * -8;
            t5.vertex[i+1] = mid[1];//base.vertices[i+4];
            t5.vertex[i+2] = mid[2];//base.vertices[i+5];
            t6.vertex[i] = mid[0] * -8;
            t6.vertex[i+1] = mid[1];//base.vertices[i+4];
            t6.vertex[i+2] = mid[2];//base.vertices[i+5];
            t7.vertex[i] = mid[0] * -8;
            t7.vertex[i+1] = mid[1];//base.vertices[i+4];
            t7.vertex[i+2] = mid[2];//base.vertices[i+5];
            t8.vertex[i] = mid[0] * -8;
            t8.vertex[i+1] = mid[1];//base.vertices[i+4];
            t8.vertex[i+2] = mid[2];//base.vertices[i+5];
        }
    }

}

void cone::setColour(std::string col)
{
    if (col=="yellow")
    {
        base.setColour("orange");
        t1.setColour("orange");
        t2.setColour("orange");
        t3.setColour("orange");
        t4.setColour("orange");
        t5.setColour("orange");
        t6.setColour("orange");
        t7.setColour("orange");
        t8.setColour("orange");
    }
}

void cone::setMidPoint(float* coordinates)
{
    float coords[3];
    calcMidPoint(coords);
    if (coords[0]!=coordinates[0])
    {
        float diff = coordinates[0] - coords[0];
        base.move("up",diff);
    }
    if (coords[1]!=coordinates[1])
    {
        float diff = coordinates[1] - coords[1];
        base.move("right",diff);
    }
    if (coords[2]!=coordinates[2])
    {
        float diff = coordinates[2] - coords[2];
        //base.move("decZ",diff);
    }
}

void cone::calcMidPoint(float* coordinates)
{
    int x=0; int y=1;int z=2;
    coordinates[x]=0;
    coordinates[y]=0;
    coordinates[z]=0;

        coordinates[x] = base.vertices[0] ;//+ t1.vertex[3];
        coordinates[y] = base.vertices[y] ;//+back.tri1[4];
        coordinates[z] = base.vertices[z] ;//+back.tri1[5];

    
  
    /*coordinates[x] /= 2;
    coordinates[y] /= 2;
    coordinates[z] /= 2;*/
}

void cone::calcPlaneMidPoint(float* coordinates)
{
    int x=0; int y=1;int z=2;
    coordinates[x]=0;
    coordinates[y]=0;
    coordinates[z]=0;

        /*coordinates[x] = base.vertices[0] ;
        coordinates[y] = base.vertices[y] ;
        coordinates[z] = base.vertices[z] ;*/
}


void multiplyMcircle(Matrix<4,4> r,float* tri)
{
    for (int i=0;i<30;i+=3)
    {
        float v[3];
            v[0] = tri[i];
            v[1] = tri[i+1];
            v[2] = tri[i+2];

            Matrix<4,1> v1;
            v1[0][0]=v[0];    v1[1][0]=v[1];    v1[2][0]=v[2];    v1[3][0]=1;
            Matrix<4,1> final;
            final = r*v1;
            final[3][0] = 1;
            tri[i] = final[0][0];    tri[i+1] = final[1][0];    tri[i+2] = final[2][0];

                tri[i] /=final[3][0];
                tri[i+1] /=final[3][0];
                tri[i+2] /=final[3][0];
    }
}
        //rotations
void cone::rotateLeftX()
{
    float angle=0.1;
    float coords[3];
    //calcMidPoint(coords);
    calcPlaneMidPoint(coords);

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
    multiplyMcircle(rotationM,base.vertices);
    multiplyM(rotationM,t1.vertex);
    multiplyM(rotationM,t2.vertex);
    multiplyM(rotationM,t3.vertex);
    multiplyM(rotationM,t4.vertex);
    multiplyM(rotationM,t5.vertex);
    multiplyM(rotationM,t6.vertex);
    multiplyM(rotationM,t7.vertex);
    multiplyM(rotationM,t8.vertex);
}

void cone::rotateRightX()
{
    float angle=-0.1;
    float coords[3];
    //calcMidPoint(coords);
    calcPlaneMidPoint(coords);

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
    multiplyMcircle(rotationM,base.vertices);
    multiplyM(rotationM,t1.vertex);
    multiplyM(rotationM,t2.vertex);
    multiplyM(rotationM,t3.vertex);
    multiplyM(rotationM,t4.vertex);
    multiplyM(rotationM,t5.vertex);
    multiplyM(rotationM,t6.vertex);
    multiplyM(rotationM,t7.vertex);
    multiplyM(rotationM,t8.vertex);
}

void cone::rotateLeftY()
{
    float angle=0.1;
    float coords[3];
    calcPlaneMidPoint(coords);

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
    multiplyMcircle(rotationM,base.vertices);
    multiplyM(rotationM,t1.vertex);
    multiplyM(rotationM,t2.vertex);
    multiplyM(rotationM,t3.vertex);
    multiplyM(rotationM,t4.vertex);
    multiplyM(rotationM,t5.vertex);
    multiplyM(rotationM,t6.vertex);
    multiplyM(rotationM,t7.vertex);
    multiplyM(rotationM,t8.vertex);
}

void cone::rotateRightY()
{
    float angle=-0.1;
    float coords[3];
    //calcMidPoint(coords);
    calcPlaneMidPoint(coords);

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
    multiplyMcircle(rotationM,base.vertices);
    multiplyM(rotationM,t1.vertex);
    multiplyM(rotationM,t2.vertex);
    multiplyM(rotationM,t3.vertex);
    multiplyM(rotationM,t4.vertex);
    multiplyM(rotationM,t5.vertex);
    multiplyM(rotationM,t6.vertex);
    multiplyM(rotationM,t7.vertex);
    multiplyM(rotationM,t8.vertex);
}

void cone::rotateLeftZ()
{
    float angle=0.1;
    float coords[3];
    //calcMidPoint(coords);
    calcPlaneMidPoint(coords);

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
    multiplyMcircle(rotationM,base.vertices);
    multiplyM(rotationM,t1.vertex);
    multiplyM(rotationM,t2.vertex);
    multiplyM(rotationM,t3.vertex);
    multiplyM(rotationM,t4.vertex);
    multiplyM(rotationM,t5.vertex);
    multiplyM(rotationM,t6.vertex);
    multiplyM(rotationM,t7.vertex);
    multiplyM(rotationM,t8.vertex);
}

void cone::rotateRightZ()
{
    float angle=-0.1;
    float coords[3];
    //calcMidPoint(coords);
    calcPlaneMidPoint(coords);

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
    multiplyMcircle(rotationM,base.vertices);
    multiplyM(rotationM,t1.vertex);
    multiplyM(rotationM,t2.vertex);
    multiplyM(rotationM,t3.vertex);
    multiplyM(rotationM,t4.vertex);
    multiplyM(rotationM,t5.vertex);
    multiplyM(rotationM,t6.vertex);
    multiplyM(rotationM,t7.vertex);
    multiplyM(rotationM,t8.vertex);

}
        //translations
void cone::move(std::string d,float diff)
{
    base.move(d,diff);
    t1.move(d,diff);
    t2.move(d,diff);
    t3.move(d,diff);
    t4.move(d,diff);
    t5.move(d,diff);
    t6.move(d,diff);
    t7.move(d,diff);
    t8.move(d,diff);
}

