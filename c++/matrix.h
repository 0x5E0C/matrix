#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>

#define PROGRAMMER	1
#define bias	PROGRAMMER

#define _matrixData(M,r,c)		*(M.data+(r-1)*M.col+c-1)
#define _matrixData_p(M,r,c)	*(M->data+(r-1)*M->col+c-1)

#define matrixData(M,r,c)	_matrixData(M,r+bias,c+bias)
#define matrixData_p(M,r,c)	_matrixData_p(M,r+bias,c+bias)

#define mtype	double

class matrix
{
public:
    int row;
    int col;
    mtype *data;
    matrix(int r,int c,char type=0);
    ~matrix();
    static void deleteMatrix(matrix *m);
    static void deleteMatrices(matrix *m[],int size);
    static matrix copyMatrix(matrix *m);
    void setMatrix(mtype arg1,...);
    void setDiagonalMatrix(mtype arg1,...);
    matrix matrixTrans();
    mtype matrixDet();
    matrix matrixInv();
    static matrix matrixMerge(matrix a,matrix b,char dir);
    static matrix matrixExtract(matrix a,int t,int l,int b,int r);
    void swapRow(int r1,int r2);
    void swapCol(int c1,int c2);
    static void matrixPrint(matrix m);
    matrix &operator=(const matrix &m)
    {
        matrix a=matrix(m.row,m.col);
        memcpy(a.data,m.data,m.row*m.col*sizeof(mtype));
        return a;
    }
    mtype &operator()(const int &r,const int &c)
    {
        return matrixData_p(this,r,c);
    }
    matrix &operator+(const matrix &m)
    {
        int i,j;
        matrix t=matrix(row,col);
        for(i=1;i<=row;i++)
        {
            for(j=1;j<=col;j++)
            {
                _matrixData(t,i,j)=_matrixData_p(this,i,j)+_matrixData(m,i,j);
            }
        }
        return t;
    }
    matrix &operator-(const matrix &m)
    {
        int i,j;
        matrix t=matrix(row,col);
        for(i=1;i<=row;i++)
        {
            for(j=1;j<=col;j++)
            {
                _matrixData(t,i,j)=_matrixData_p(this,i,j)-_matrixData(m,i,j);
            }
        }
        return t;
    }
    matrix &operator*(const matrix &m)
    {
        int i,j,k;
        matrix t=matrix(row,m.col);
        for(i=1;i<=row;i++)
        {
            for(j=1;j<=m.col;j++)
            {
                for(k=1;k<=col;k++)
                {
                    _matrixData(t,i,j)+=_matrixData_p(this,i,k)*_matrixData(m,k,j);
                }
            }
        }
        return t;
    }
    template <typename T>
    matrix operator*(const T &s)
    {
        int i,j;
        matrix t=matrix(row,col);
        for(i=1;i<=row;i++)
        {
            for(j=1;j<=col;j++)
            {
                _matrixData(t,i,j)=s*_matrixData_p(this,i,j);
            }
        }
        return t;
    }
};



#endif
