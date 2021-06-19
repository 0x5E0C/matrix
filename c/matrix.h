#ifndef MATRIX_H_
#define MATRIX_H_

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

typedef struct matrix
{
	int row;
	int col;
	mtype *data;
} matrix;

matrix createMatrix(int row,int col);
matrix createIdentityMatrix(int order);
void deleteMatrix(matrix *m);
void deleteMatrices(matrix *m[],int size);
matrix copyMatrix(matrix m);
void setMatrix(matrix *m,mtype arg1,...);
void setDiagonalMatrix(matrix *m,mtype arg1,...);
matrix matrixAdd(matrix a,matrix b);
matrix matrixSub(matrix a,matrix b);
matrix matrixMul(matrix a,matrix b);
matrix matrixScalarMul(mtype a,matrix b);
matrix matrixTrans(matrix a);
mtype matrixDet(matrix t);
matrix matrixInv(matrix a);
matrix matrixMerge(matrix a,matrix b,char dir);
matrix matrixExtract(matrix a,int t,int l,int b,int r);
void swapRow(matrix *m,int r1,int r2);
void swapCol(matrix *m,int c1,int c2);
void matrixPrint(matrix m);

#endif
