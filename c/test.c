#include "matrix.h"

int main()
{
    //例程参数设置：PROGRAMMER：1，mtype：double

    matrix a=createMatrix(2,4);                     //创建一个2x4的空矩阵
    matrix b=createIdentityMatrix(4);               //创建一个4x4的单位矩阵
    setMatrix(&a,1.0,0.0,3.0,1.0,\
                 2.0,1.0,0.0,2.0);                  //设置矩阵a的数据
    setDiagonalMatrix(&b,2.0,5.0,3.0,8.0);          //设置矩阵b的对角线数据
    matrixPrint(a);                                 //打印a矩阵
    matrixPrint(b);                                 //打印b矩阵
    printf("%lf\n",matrixData(a,1,1));				//打印第2行第2列的数据（访问matrix*类型用matrixData_p）

    matrix c=copyMatrix(a);                         //拷贝矩阵
    matrixPrint(c);
    matrix d=matrixScalarMul(3.0,a);                //矩阵数乘（数字只能放右边）
    matrixPrint(d);
    matrix e=matrixMul(a,b);                        //矩阵相乘
    matrixPrint(e);
    matrix f=matrixAdd(a,d);                        //矩阵相加
    matrixPrint(f);
    matrix g=matrixSub(d,a);                        //矩阵相减
    matrixPrint(g);
    matrix h=matrixTrans(a);                        //矩阵转置
    matrixPrint(h);
    printf("%lf\n",matrixDet(b));                   //求方阵行列式
    matrix i=matrixInv(b);                          //求方阵逆矩阵
    matrixPrint(i);
    matrix j=matrixMerge(a,d,'r');                  //矩阵拼接（'r'：右拼接）
    matrixPrint(j);
    matrix k=matrixMerge(a,d,'b');                  //矩阵拼接（'b'：下拼接）
    matrixPrint(k);


    matrix l=matrixExtract(b,1,0,3,2);             //矩阵截取（将b矩阵2-4行，1-3行取出）
    matrixPrint(l);
    swapRow(&a,0,1);                                //交换a矩阵的第1、2行（改变原始数据）
    matrixPrint(a);
    swapCol(&b,1,2);                                //交换a矩阵的第2、3列（改变原始数据）
    matrixPrint(b);


    deleteMatrix(&a);                               //free申请的内存
    matrix *n[]={&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l};
    deleteMatrices(n,sizeof(n)/sizeof(matrix*));    //批量free内存


    return 0;
}
