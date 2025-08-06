#include "Matrix.cpp"
#include "Vector.cpp"

#include <iostream>
#include <sstream>

using namespace std;

void vectorTest(){
    Vector<2> a;
    a.print();

    double *ar = new double[3];
    for (int i=0;i<3; i++)
    {
        ar[i] = i;
    }
    Vector<3> b(ar);
    b.print();

    Vector<3> c(b);
    c.print();


    Vector<3> d;
    d = b+c;
    d.print();
    d = b-c;
    d.print();
    double num = b*c;
    std::cout <<"Dot Product: " << num <<endl;
    d = b*2;
    d.print();
    double mag = d.magnitude();
    std::cout << "Magnitude: " << mag <<endl;
    Vector<3> e;
    e=d;
    e.print();
    (d.crossProduct(c)).print();
    (d.unitVector()).print();
}

void matrixTest()
{
    Vector<2> a;
    a.print();

    double *ar = new double[3];
    for (int i=0;i<3; i++)
    {
        ar[i] = i;
    }
    Vector<3> b(ar);
    b.print();

    Vector<3> c(b);
    c.print();


    Vector<3> d;
    d = b+c;
    d.print();
    d = b-c;
    d.print();
    double num = b*c;
    std::cout <<"Dot Product: " << num <<endl;
    d = b*2;
    d.print();
    double mag = d.magnitude();
    std::cout << "Magnitude: " << mag <<endl;
    Vector<3> e;
    e=d;
    e.print();
    (d.crossProduct(c)).print();
    (d.unitVector()).print();
    

    Matrix<3, 3> m;
    m.print();
    std::cout << std::endl;
    double **array = new double*[3];
    for (int i=0;i<3;i++)
    {
        array[i] = new double[3];
    }
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
                array[i][j] = i+j;
        }
    }
    int numb=4;
    double **array2 = new double*[numb];
    for (int i=0;i<numb;i++)
    {
        array2[i] = new double[numb];
    }
    for (int i=0; i<numb; i++)
    {
        for (int j=0; j<numb; j++)
        {
                array2[i][j] = i+j;
        }
    }
    Matrix<3,3> f(array);
    f.print();
    Matrix<3,3> g(f);
    g.print();
    Matrix<3,3> h;
    h=f;
    h.print();

    std::cout << std::endl;
    (f+h).print();
    std::cout << std::endl;
    (f*h).print();

    Matrix<1,3> i;
    Matrix<3,1> j;
    (i*j).print();

    SquareMatrix<4> k(array2);
    k.print();

    IdentityMatrix<4> l;
    l.print();
    std::cout << std::endl;

    m = f*h;
    m.print();
    h = ~m;
    h.print();

    k.print();
    try{
        std::cout << "Determinant: " << k.determinant() <<std::endl;
    }catch (const exception& e){
        std::cerr <<e.what() <<endl;
    }
    double **array3 = new double*[3];
    for (int i=0;i<3;i++)
    {
        array3[i] = new double[3];
    }
    array3[0][0]=20;array3[0][1]=-3;array3[0][2]=9;
    array3[1][0]=2;array3[1][1]=7;array3[1][2]=-1;
    array3[2][0]=6;array3[2][1]=1;array3[2][2]=0;
    SquareMatrix<3> n(array3);
    n.print();
    try{
    std::cout << "Determinant: " << n.determinant() <<std::endl;
    }catch (const exception& e){
        std::cerr <<e.what() <<endl;
    }
    (!n).print();
    try{
        k.print();
        (!k).print();
    }catch (const exception& e){
        std::cerr <<e.what() <<endl;
    }
    l.print();
    try{
        (!n).print();
    }catch (const exception& e){
        std::cerr <<e.what() <<endl;
    }
    IdentityMatrix<2> i2;
    i2.print();
    try{
        (!i2).print();
    }catch (const exception& e){
        std::cerr <<e.what() <<endl;
    }
    try{
        (!l).print();
    }catch (const exception& e){
        std::cerr <<e.what() <<endl;
    }
    n.solve(c);
}

void vectorTest2()
{
    double *ar = new double[3];
    ar[0]=1;
    ar[1]=1;
    ar[2]=-1;
    double *w = new double[3];
    w[0]=-1;
    w[1]=4;
    w[2]=1;
    Vector<3> v1(ar);
    Vector<3> v2(w);
    v1.print();
    v2.print();
    (v1.crossProduct(v2)).print();
}

void matrixTest2()
{
    double **a1 = new double*[3];
    for (int i=0;i<3;i++)
    {
        a1[i] = new double[3];
    }
    a1[0][0]=-7;a1[0][1]=7;a1[0][2]=7;
    a1[1][0]=-8;a1[1][1]=-2;a1[1][2]=9;
    a1[2][0]=1;a1[2][1]=-6;a1[2][2]=-6;
    Matrix<3,3> A(a1);

    double **a2 = new double*[3];
    for (int i=0;i<3;i++)
    {
        a2[i] = new double[4];
    }
    a2[0][0]=5;a2[0][1]=-8; a2[0][2]=7;a2[0][3]=9;
    a2[1][0]=3;a2[1][1]=-7;a2[1][2]=3;a2[1][3]=6;
    a2[2][0]=-0;a2[2][1]=9;a2[2][2]=-4;a2[2][3]=-2;
    Matrix<3,4> B(a2);

    A.print();
    std::cout << std::endl;
    B.print();

    (A*B).print();
}

void matrixTest3()
{
    double **a1 = new double*[2];
    for (int i=0;i<2;i++)
    {
        a1[i] = new double[3];
    }
    a1[0][0]=-7;a1[0][1]=7;a1[0][2]=7;
    a1[1][0]=-7;a1[1][1]=7;a1[1][2]=7;
    
    Matrix<2,3> A(a1);
    A.print();
    (~A).print();
}

void matrixTest4()
{
    double **a1 = new double*[2];
    for (int i=0;i<2;i++)
    {
        a1[i] = new double[2];
    }
    a1[0][0]=1;a1[0][1]=-4;
    a1[1][0]=3;a1[1][1]=1;
    SquareMatrix<2> A(a1);

    double *w = new double[2];
    w[0]=-21;
    w[1]=16;
    Vector<2> v1(w);

    (!A).print();
    (A.solve(v1)).print();
}

void CT2()
{
    double *ar = new double[3];
    ar[0] = ;
    ar[1] = i;
    ar[2] = i;
    Vector<3> b(ar);
    b.print();
}

int main(int argc, char const *argv[])
{
    //vectorTest();
    //matrixTest();
    //vectorTest2();
    //matrixTest2();
    //matrixTest3();
    //matrixTest4();
    CT2();
}
