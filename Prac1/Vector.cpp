#include "Vector.h"

template <int n> //size of vector
Vector<n>::Vector()
{
    //initialise array using the template argument
    arr = new double[n];
    for (int i=0; i<n; i++)
    {
        arr[i] = 0.0;
    }
}

template <int n>
Vector<n>::Vector(double *arr)
{
    // shallow copy array
    this->arr = arr;
}

template <int n>
Vector<n>::~Vector()
{
    //free memory
    if (arr!=NULL)
    {
        delete [] arr;
        arr=NULL;
    }
}

template <int n>
Vector<n>::Vector(const Vector<n> &other)
{
    // copy constructor = deep copy
    this->arr = new double[other.getN()];
    //arr is private -> other classes cannot access, but same class can
    for (int i=0;i<n;i++)
    {
        this->arr[i] = other.arr[i];
    }
}

template <int n>
Vector<n>::Vector(const Matrix<n, 1> &other)
{
    //constructor: create vector from matrix
    this->arr = new double[other.getN()];
    //arr is protected in matrix -> cannot access directly from vector :(
    for (int i=0;i<n;i++)
    {
        this->arr[i] = other[i][0]; //use subscript operator of matrix to get values
    }
}

template <int n>
Vector<n> &Vector<n>::operator=(const Vector<n> &other)
{
    //assignment operator
    if (&other == this){
        return *this;
    }
    if (this->arr!=NULL)
    {
        delete [] this->arr;
        this->arr = NULL;
    }
    this->arr = new double[other.getN()];
    for (int i=0; i<n; i++)
    {
        this->arr[i] = other.arr[i];
    }

    return *this;
}

template <int n>
Vector<n> Vector<n>::operator+(const Vector rhs) const
{
    // add 2 vectors
    if (this->getN()!=rhs.getN())
    {
        Vector<n> emptyVector;
        return emptyVector;
    }

    double *a = new double[this->getN()];
    for (int i=0; i<n; i++)
    {
        a[i] = this->arr[i] + rhs.arr[i];
    }

    Vector<n> resultVector(a);
    return resultVector;
}

template <int n>
Vector<n> Vector<n>::operator-(const Vector<n> rhs) const
{
    // subtract 2 vectors
    if (this->getN()!=rhs.getN())
    {
        Vector<n> emptyVector;
        return emptyVector;
    }

    double *a = new double[this->getN()];
    for (int i=0; i<n; i++)
    {
        a[i] = this->arr[i] - rhs.arr[i];
    }

    Vector<n> resultVector(a);
    return resultVector;
}

template <int n>
Vector<n> Vector<n>::operator*(const double val) const //Scalar value
{
    //multiply each vector value by val
    double *a = new double[this->getN()];
    for (int i=0; i<n; i++)
    {
        a[i] = this->arr[i] * val;
    }

    Vector<n> resultVector(a);
    return resultVector;
}

template <int n>
double Vector<n>::operator*(const Vector<n> rhs) const //DOT PRODUCT
{
    // *Each value at same index
    if (this->getN()!=rhs.getN())
    {
        return 0;
    }
    
    double dotProduct = 0.0;
    for (int i=0; i<this->getN(); i++)
    {
        dotProduct += (this->arr[i]*rhs.arr[i]);
    }

    return dotProduct;
}

template <int n>
double Vector<n>::magnitude() const // ||v||
{
    double mag = 0.0;
    for (int i=0; i<this->getN(); i++)
    {
        mag += pow(this->arr[i],2);
    }

    mag = sqrt(mag);
    return mag;
}

template <int n>
Vector<n>::operator Matrix<n, 1>() const
{
    // conversion operator: return N*1 matrix
    double **a = new double*[this->getN()];
    for (int i=0; i<n; i++)
    {
        a[i] = new double[1];
        a[i][0] = arr[i];
    }
    Matrix<n,1> resultMatrix(a);
    return resultMatrix;
}

template <>
Vector<3> Vector<3>::crossProduct(const Vector<3> rhs) const
{
    // in order to actually do cross product, both vectors MUST HAVE 3 values
    if (this->getN()!=3 || rhs.getN()!=3)
    {
        Vector<3> emptyVector;
        return emptyVector;
    }
    //(u2v3-u3v2, u3v1-u1v3, u1v2-u2v1)
    double *a = new double[3];
    a[0] = (this->arr[1]*rhs.arr[2]) - (this->arr[2]*rhs.arr[1]); //u2v3-u3v2
    a[1] = (this->arr[2]*rhs.arr[0]) - (this->arr[0]*rhs.arr[2]); //u3v1-u1v3
    a[2] = (this->arr[0]*rhs.arr[1]) - (this->arr[1]*rhs.arr[0]); //u1v2-u2v1

    Vector<3> resultVector(a);
    return resultVector;
}

template <int n>
Vector<n> Vector<n>::unitVector() const
{
    //1. calc magnitude
    double mag = this->magnitude();
    if (mag==0)
    {
        throw std::runtime_error("Invalid unit vector");
    }
    double num = 1/mag;
    
    double *a = new double[this->getN()];
    for (int i=0; i<n; i++)
    {
        a[i] = this->arr[i] * num;
    }

    Vector<n> resultVector(a);
    return resultVector;
}

template <int n>
int Vector<n>::getN() const
{
    return n;
}
