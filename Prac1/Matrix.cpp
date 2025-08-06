#include "Matrix.h"

double determinantHelp(double **arr,int num);

template <int n, int m>
Matrix<n, m>::Matrix()
{
    //constructor
    if (n<0 || m<0)
    {
        return;
    }
    arr = new double*[n];
    for (int i=0;i<n;i++)
    {
        arr[i] = new double[m];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
                arr[i][j] = 0;
        }
    }
}

template <int n, int m>
Matrix<n, m>::Matrix(double **otherArr)
{
    // shallow copy
    this->arr = otherArr;
}

template <int n, int m>
Matrix<n, m>::Matrix(const Matrix &other)
{
    // copy constructor: deep copy
    arr = new double*[n];
    for (int i=0;i <n; i++)
    {
        arr[i] = new double[m];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
                arr[i][j] = other.arr[i][j];
        }
    }
}

template <int n, int m>
Matrix<n, m>::~Matrix()
{
    // free memory
    if (arr!=NULL)
    {
        for (int i=0;i <n; i++)
        {
            if (arr[i]!=NULL)
            {
                delete arr[i];
                arr[i] = NULL;
            }
        }

        delete[] arr;
        arr=NULL;
    }
}

template <int n, int m>
template <int a>
Matrix<n, a> Matrix<n, m>::operator*(const Matrix<m, a> rhs) const
{
    // multiply 2 matrices
    if (this->getM()!=rhs.getN()) //multiplication not possible if cols of A not = rows of B
    {
        Matrix<n,a> emptyMatrix;
        return emptyMatrix;
    }

    double **ar = new double*[n];
    for (int i=0;i<n;i++)
    {
        ar[i] = new double[a];
    }

    for (int i=0; i<n ;i++)
    {
        for (int k=0; k<a; k++)
        {
            //int num=0;
            double val=0.0;
            for (int j=0; j<m; j++)
            {
                val += arr[i][j] * rhs[j][k]; 
            }
            ar[i][k] = val;
            //num++;
        }
    }

    Matrix<n,a> resultMatrix(ar);
    return resultMatrix;
}

template <int n, int m>
Matrix<n, m> Matrix<n, m>::operator*(const double val) const
{
    // scalar multiplication
    double **a = new double*[n];
    for (int i=0;i<n;i++)
    {
        a[i] = new double[m];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
                a[i][j] = this->arr[i][j]*val;
        }
    }

    Matrix<n,m> resultMatrix(a);
    return resultMatrix;
}

template <int n, int m>
Matrix<n, m> Matrix<n, m>::operator+(const Matrix<n, m> rhs) const
{
    // add 2 matrices
    if (this->getN()!=rhs.getN() || this->getN()!=rhs.getN()) 
    {
        Matrix<n,m> emptyMatrix;
        return emptyMatrix;
    }

    double **a = new double*[n];
    for (int i=0;i<n;i++)
    {
        a[i] = new double[m];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
                a[i][j] = this->arr[i][j] + rhs.arr[i][j];
        }
    }

    Matrix<n,m> resultMatrix(a);
    return resultMatrix;
}


double** calcCof(double **arr,int num,int r,int c)
{
    //calculate minors
    double **minor = new double*[num-1];
    for (int i=0;i<num-1;i++)
    {
        minor[i] = new double[num-1];
    }
    int row=0;
    for (int i=0; i<num; i++)
    {
        int col=0;
        if (i!=r)
        {
            for (int j=0; j<num; j++)
            {
                if (i!=r && j!=c)
                {
                    minor[row][col] = arr[i][j];
                    col++;
                }
            }
            row++;
        }
    }
    return minor;
}
template <int n> //N*N matrices
SquareMatrix<n> SquareMatrix<n>::operator!() const
{
    // inverse of matrix = (1/determinant) * Adjoint
    //get determinant
    double det = this->determinant();
    if (det==0)
    {
        throw std::runtime_error("Inverse does not exist");
        SquareMatrix<n> empty;
        return empty;
    }
    double val = 1/det;

    //to get ADJOINT = transpose[cof(matrix)]
    //cofactor matrix
    double **a = new double*[n];
    for (int i=0;i<n;i++)
    {
        a[i] = new double[n];
    }

    if (n<=1)
    {
        SquareMatrix<n> emptyMatrix(this->arr);
        return emptyMatrix;
    }
    /*if (n==2)
    {
        a[0][0] = this->arr[1][1];
        a[0][1] = this->arr[1][0]*-1;
        a[1][0] = this->arr[0][1]*-1;
        a[1][1] = this->arr[0][0];
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                a[i][j] *= val;
            }
        }
        
        SquareMatrix<n> resultMatrix(a);
        return resultMatrix;
    }*/

    //calculate adjoint matrix -> calc coefficients
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            double** minMatrix = calcCof(this->arr,n,i,j);
            double det2 = determinantHelp(minMatrix,n-1);
            if ((i+j)%2 != 0)
            {
                det2 *= -1;
                if (det2==-0)
                {
                    det2*=-1;
                }
            }
            a[i][j]= det2;

            /*if (minMatrix!=NULL)
            {
                for (int r=0; r<n; r++)
                {
                    if (minMatrix[r]!=NULL)
                    {
                        delete minMatrix[r];
                        minMatrix[r] = NULL;
                    }
                }
                delete [] minMatrix;
                minMatrix=NULL;
            }*/
        }
    }

    //transpose matrix:
    double **t = new double*[n];
    for (int i=0;i<n;i++)
    {
        t[i] = new double[n];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            t[i][j] = a[j][i];
        }
    }
    if (a!=NULL)
    {
        for (int i=0; i<n; i++)
        {
            if (a[i]!=NULL)
                delete a[i];
        }
        delete [] a;
        a=NULL;
    }

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            t[i][j] *= val;
        }
    }
    SquareMatrix<n> resultMatrix(t);
    return resultMatrix;
}

template <int n, int m>
Matrix<m, n> Matrix<n, m>::operator~() const
{
    // transpose matrix = swap rows and columns
    Matrix<m,n> resultMatrix;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
                resultMatrix[j][i] = this->arr[i][j];
        }
    }

    return resultMatrix;
}

template <int n, int m>
int Matrix<n, m>::getM() const
{
    return m;
}

template <int n, int m>
int Matrix<n, m>::getN() const
{
    return n;
}

template <int n>
SquareMatrix<n>::SquareMatrix()
{
    //constructor
    if (n<0)
    {
        return;
    }
    this->arr = new double*[n];
    for (int i=0;i<n;i++)
    {
        this->arr[i] = new double[n];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
                this->arr[i][j] = 0;
        }
    }
}

template <int n>
SquareMatrix<n>::SquareMatrix(double **arr)
{
    if (n<0)
    {
        return;
    }
    this->arr = arr;
    /*this->arr = new double*[n];
    for (int i=0;i<n;i++)
    {
        this->arr[i] = new double[n];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
                this->arr[i][j] = arr[i][j];
        }
    }*/
}

template <int n>
SquareMatrix<n>::~SquareMatrix()
{
    // free memory
    if (this->arr!=NULL)
    {
        for (int i=0;i <n; i++)
        {
            if (this->arr[i]!=NULL)
            {
                delete this->arr[i];
                this->arr[i] = NULL;
            }
        }

        delete[] this->arr;
        this->arr=NULL;
    }
}

template <int n>
Vector<n> SquareMatrix<n>::solve(const Vector<n> vec) const
{
    //linear equation -> this=coefficient matrix, vec=constants
    //X = inverse(this) * vec
    //get inverse matrix
    Matrix<n,n> inverseMatrix = this->operator!() ;
    //multiply iinverse with vec
    Matrix<n,1> vecMatrix = vec;
    Matrix<n,1> multMatrix = inverseMatrix * vecMatrix;
    Vector<n> resultVector(multMatrix);

    return resultVector;
}


double determinantHelp(double **arr,int num)
{
    if (num<=0)
    {
        return 1;
    }
    if (num==1)
    {
        return arr[0][0];
    }
    if (num==2)
    {
        double det=0.0;
        det = ((arr[0][0])*(arr[1][1])) - ((arr[0][1])*(arr[1][0]));
        return det;
    }
    if (num>2){

        double total=0.0;
            for (int it=0; it<num ;it++) //need to break up matrix into multiple smaller matrices
            {
                double **a = new double*[num-1];
                for (int i=0;i<num-1;i++)
                {
                    a[i] = new double[num-1];
                }
                int row=0;
                for (int i=1; i<num; i++)
                {
                    int col=0;
                    for (int j=0; j<num; j++)
                    {
                        if (j!=it) //cannot add current column to new matrix
                        {
                            a[row][col] = arr[i][j];
                            col++;
                        }
                    }
                    row++;
                }
                //SquareMatrix<n-1> newMatrix(a);
                double val =  arr[0][it]* determinantHelp(a,num-1);
                if (it%2 != 0)
                {
                    val *= -1;
                }
                total +=val;
            }

        return total;
    }
    return 0;
}

template <int n>
double SquareMatrix<n>::determinant() const
{
    if (n<=0)
    {
        return 1;
    }
    if (n==1)
    {
        return this->arr[0][0];
    }
    if (n==2)
    {
        double det=0.0;
        det = ((this->arr[0][0])*(this->arr[1][1])) - ((this->arr[0][1])*(this->arr[1][0]));
        if (det==0)
        {
            throw std::runtime_error("Unsolvable set of linear equations");
            //return 0;
        }
        return det;

    }else if (n>=3){
        double total=0.0;
            for (int it=0; it<n ;it++) //need to break up matrix into multiple smaller matrices
            {
                double **a = new double*[n-1];
                for (int i=0;i<n-1;i++)
                {
                    a[i] = new double[n-1];
                }
                int row=0;
                for (int i=1; i<n; i++)
                {
                    int col=0;
                    for (int j=0; j<n; j++)
                    {
                        if (j!=it) //cannot add current column to new matrix
                        {
                            a[row][col] = this->arr[i][j];
                            col++;
                        }
                    }
                    row++;
                }
                //SquareMatrix<n-1> newMatrix(a);
                //double d = newMatrix.determinant();
                double val =  this->arr[0][it] * determinantHelp(a,n-1);
                if (it%2 != 0)
                {
                    val *= -1;
                }
                total +=val;
            }
        if (total==0)
        {
            throw std::runtime_error("Unsolvable set of linear equations");
        }
        return total;
    }
    return 0;
}



template <int n>
IdentityMatrix<n>::IdentityMatrix()
{
    // consists of 1 and 0
    this->arr = new double*[n];
    for (int i=0;i<n;i++)
    {
        this->arr[i] = new double[n];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
                if (i==j)
                {
                    this->arr[i][j] = 1;  
                }else
                {
                    this->arr[i][j] = 0;
                }
        }
    }
}

template <int n>
IdentityMatrix<n>::~IdentityMatrix()
{
    if (this->arr!=NULL)
    {
        for (int i=0;i <n; i++)
        {
            if (this->arr[i]!=NULL)
            {
                delete this->arr[i];
                this->arr[i] = NULL;
            }
        }

        delete[] this->arr;
        this->arr=NULL;
    }
}

template <int n, int m>
inline Matrix<n, m> &Matrix<n, m>::operator=(const Matrix<n, m> &other)
{
    if (&other == this){
       return *this;
    }

    if (arr!=NULL)
    {
        for (int i=0;i <n; i++)
        {
            if (arr[i]!=NULL)
            {
                delete arr[i];
                arr[i] = NULL;
            }
        }

        delete[] arr;
        arr=NULL;
    }

    arr = new double*[n];
    for (int i=0;i <n; i++)
    {
        arr[i] = new double[m];
    }
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
                arr[i][j] = other.arr[i][j];
        }
    }

    return *this;
}
