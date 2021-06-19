#include "matrix.h"

int main()
{
    matrix a=matrix(2,4);                       //创建一个2x4的空矩阵
    matrix b=matrix(4,4,'i');                   //创建一个4x4的单位矩阵
    a.setMatrix(1.0,0.0,3.0,1.0,\
                2.0,1.0,0.0,2.0);               //设置矩阵a的数据
    b.setDiagonalMatrix(2.0,5.0,3.0,8.0);       //设置矩阵b的对角线数据
    matrix::matrixPrint(a);                     //打印a矩阵
    matrix::matrixPrint(b);                     //打印b矩阵


    matrix c=a;                                 //拷贝矩阵（浅拷贝）
    matrix::matrixPrint(c);
    matrix d=matrix::copyMatrix(&a);            //拷贝矩阵（深拷贝）
    matrix::matrixPrint(d);
    matrix e=a*3;                               //矩阵数乘（数字只能放右边）
    matrix::matrixPrint(e);
    matrix f=a+d;                               //矩阵相加
    matrix::matrixPrint(f);
    matrix g=d-a;                               //矩阵相减
    matrix::matrixPrint(g);
    matrix h=a.matrixTrans();                   //矩阵转置
    matrix::matrixPrint(h);
    printf("%lf\n",b.matrixDet());              //求方阵行列式
    matrix i=b.matrixInv();                     //求方阵逆矩阵
    matrix::matrixPrint(i);


    matrix j=matrix::matrixMerge(a,d,'r');      //矩阵拼接（'r'：右拼接）
    matrix::matrixPrint(j);
    matrix k=matrix::matrixMerge(a,d,'b');      //矩阵拼接（'b'：下拼接）
    matrix::matrixPrint(k);


    matrix l=matrix::matrixExtract(b,1,0,3,2);  //矩阵截取（将b矩阵2-4行，1-3行取出）
    matrix::matrixPrint(l);
    a.swapRow(0,1);                             //交换a矩阵的第1、2行（改变原始数据）
    matrix::matrixPrint(a);
    b.swapCol(1,2);                             //交换a矩阵的第2、3列（改变原始数据）
    matrix::matrixPrint(b);


    matrix *m;
    m=&a;
    matrixData_p(m,0,0)=3.0;                    //通过指针改变第1行第1列内容，2.0->3.0
    printf("%lf\n",matrixData_p(m,0,0));        //通过指针访问第1行第1列内容
    matrixData(a,0,0)=9.0;                      //通过指针改变第1行第1列内容，3.0->9.0，（等效于a(0,0)=9）
    printf("%lf\n",matrixData(a,0,0));          //通过指针访问第1行第1列内容
    b(2,1)=5.0;                                 //改变第3行第2列内容，3.0->5.0
    printf("%lf\n",b(2,1));                     //打印b的第3行第2列内容


    matrix::deleteMatrix(&a);                   //free申请的内存
    matrix *n[]={&b,&d,&e,&f,&g,&h,&i,&j,&k,&l};//c是从a浅拷贝来的，只free掉a的内存
    matrix::deleteMatrices(n,sizeof(n)/sizeof(matrix*));//批量free内存


    return 0;
}
