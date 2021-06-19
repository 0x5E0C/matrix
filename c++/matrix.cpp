#include "matrix.h"

/*****************************************************/
/*函数名：matrix                                 	 */
/*参数：矩阵的行大小，列大小，类型（i或I为单位矩阵） */
/*返回值：创建的矩阵                             	 */
/*功能：构造函数，创建指定大小的矩阵			 	 */
/*****************************************************/
matrix::matrix(int r,int c,char type)
{
    int i;
    row=r;
    col=c;
    data=new mtype[row*col];
    memset(data,0,row*col*sizeof(mtype));
    if(type=='i' || type=='I')
    {
        for(i=1;i<=r;i++)
        {
            _matrixData_p(this,i,i)=1;
        }
    }
}

matrix::~matrix()
{

}

/********************************/
/*函数名：deleteMatrix          */
/*参数：矩阵的指针              */
/*返回值：无                    */
/*功能：释放该矩阵申请的内存    */
/********************************/
void matrix::deleteMatrix(matrix *m)
{
    delete[] m->data;
}

/****************************************/
/*函数名：deleteMatrices                */
/*参数：矩阵列表的指针                  */
/*返回值：无                            */
/*功能：释放该矩阵列表内的矩阵申请的内存*/
/****************************************/
void matrix::deleteMatrices(matrix *m[],int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        deleteMatrix(m[i]);
    }
}

/********************************/
/*函数名：copyMatrix            */
/*参数：待拷贝矩阵              */
/*返回值：拷贝出的矩阵          */
/*功能：拷贝矩阵                */
/********************************/
matrix matrix::copyMatrix(matrix *m)
{
    matrix a=matrix(m->row,m->col);
    memcpy(a.data,m->data,m->row*m->col*sizeof(mtype));
    return a;
}

/********************************/
/*函数名：setMatrix             */
/*参数：待赋值矩阵，赋值数据    */
/*返回值：无                    */
/*功能：给矩阵赋值              */
/********************************/
void matrix::setMatrix(mtype arg1,...)
{
	va_list valist;
    int i;
    va_start(valist,arg1);
    *data=arg1;
    for(i=1;i<row*col;i++)
    {
       *(data+i)=va_arg(valist,double);
    }
    va_end(valist);
}

/********************************/
/*函数名：setDiagonalMatrix     */
/*参数：待赋值矩阵，赋值数据    */
/*返回值：无                    */
/*功能：给矩阵的对角线赋值      */
/********************************/
void matrix::setDiagonalMatrix(mtype arg1,...)
{
	va_list valist;
    int i;
    va_start(valist,arg1);
    *data=arg1;
    for(i=2;i<=row;i++)
    {
       _matrixData_p(this,i,i)=va_arg(valist,double);
    }
    va_end(valist);
}

/********************************/
/*函数名：matrixTrans	   		*/
/*参数：无						*/
/*返回值：转置结果				*/
/*功能：矩阵转置				*/
/********************************/
matrix matrix::matrixTrans()
{
	int i,j;
    matrix m=matrix(col,row);
    for(i=1;i<=row;i++)
	{
        for(j=1;j<=col;j++)
		{
            _matrixData(m,j,i)=_matrixData_p(this,i,j);
		}
	}
	return m;
}

/********************************/
/*函数名：matrixDet		   		*/
/*参数：无						*/
/*返回值：行列式的结果			*/
/*功能：求矩阵的行列式			*/
/********************************/
mtype matrix::matrixDet()
{
    matrix m=copyMatrix(this);
    int i,j,k=1,h=1,a,b;
	int order=m.row;
	mtype mul;
	mtype result=1,flag=1;
	for(a=2;a<=order;a++)
	{
		for(i=a;i<=order;i++)
		{
			if(_matrixData(m,a-1,k)==0)
			{
                for(b=a;b<=order;b++)
                {
                    if(_matrixData(m,b,k)!=0)
                    {
                        swapRow(a-1,b);
                        flag*=-1;
                        break;
                    }
                }
			}
            if(_matrixData(m,a-1,k)==0)
            {
                return 0;
            }
			mul=_matrixData(m,i,k)/_matrixData(m,a-1,k);
			for(j=a-1;j<=order;j++)
			{
				_matrixData(m,i,j)=_matrixData(m,i,j)-mul*_matrixData(m,h,j);
			}
        }
		k++;
		h++;
	}
	for(i=1;i<=order;i++)
	{
		result*=_matrixData(m,i,i);
	}
    deleteMatrix(&m);
	return flag*result;
}

/********************************/
/*函数名：matrixInv		   		*/
/*参数：无						*/
/*返回值：逆矩阵				*/
/*功能：求矩阵的逆矩阵			*/
/********************************/
matrix matrix::matrixInv()
{
    int i,j,l;
    int order=row;
    double mul;
    matrix t=matrix(row,col,'i');
    matrix a=copyMatrix(this);
    matrix m=matrixMerge(a,t,'r');
    for(l=1;l<=order;l++)
    {
        mul=_matrixData(m,l,l);
        for(i=l;i<=2*order;i++)
        {
            _matrixData(m,l,i)/=mul;
        }
        for(i=1;i<=m.row;i++)
        {
            if(i==l)
            {
                continue;
            }
            mul=_matrixData(m,i,l);
            for(j=1;j<=2*order;j++)
            {
                _matrixData(m,i,j)=_matrixData(m,i,j)-mul*_matrixData(m,l,j);
            }
        }
    }
    matrix result=matrixExtract(m,1-bias,order+1-bias,order-bias,2*order-bias);
    deleteMatrix(&t);
    deleteMatrix(&a);
    deleteMatrix(&m);
    return result;
}

/********************************************************/
/*函数名：matrixMerge	   								*/
/*参数：待合并的两个矩阵，方向（r：右合并，b：下合并）	*/
/*返回值：合并后的矩阵									*/
/*功能：合并矩阵										*/
/********************************************************/
matrix matrix::matrixMerge(matrix a,matrix b,char dir)
{
    int i,j;
	if(dir=='r')
    {
        matrix m=matrix(a.row,a.col+b.col);
		for(i=1;i<=a.row;i++)
		{
			for(j=1;j<=a.col;j++)
			{
                _matrixData(m,i,j)=_matrixData(a,i,j);
			}
			for(j=a.col+1;j<=a.col+b.col;j++)
			{
                _matrixData(m,i,j)=_matrixData(b,i,j-a.col);
			}
		}
        return m;
	}
	else if(dir=='b')
    {
        matrix m=matrix(a.row+b.row,a.col);
		for(i=1;i<=a.col;i++)
		{
			for(j=1;j<=a.row;j++)
			{
                _matrixData(m,j,i)=_matrixData(a,j,i);
			}
			for(j=a.row+1;j<=a.row+b.row;j++)
			{
                _matrixData(m,j,i)=_matrixData(b,j-a.row,i);
			}
		}
        return m;
    }
    return a;
}

/****************************************************/
/*函数名：matrixExtract	   							*/
/*参数：待截取矩阵，开始截取的行，列，结束的行，列	*/
/*返回值：逆矩阵									*/
/*功能：求矩阵的逆矩阵								*/
/****************************************************/
matrix matrix::matrixExtract(matrix a,int t,int l,int b,int r)
{
	int i,j;
    matrix m=matrix(b-t+1,r-l+1);
	l+=bias;
	t+=bias;
	r+=bias;
	b+=bias;
	for(i=t;i<=b;i++)
	{
		for(j=l;j<=r;j++)
        {
			_matrixData(m,i-t+1,j-l+1)=_matrixData(a,i,j);
		}
	}
	return m;
}

/********************************/
/*函数名：swapRow		   		*/
/*参数：交换的两行				*/
/*返回值：无					*/
/*功能：交换矩阵的行			*/
/********************************/
void matrix::swapRow(int r1,int r2)
{
	int i;
    mtype temp;
    r1+=bias;
    r2+=bias;
    for(i=1;i<=col;i++)
	{
        temp=_matrixData_p(this,r1,i);
        _matrixData_p(this,r1,i)=_matrixData_p(this,r2,i);
        _matrixData_p(this,r2,i)=temp;
	}
}

/********************************/
/*函数名：swapCol		   		*/
/*参数：矩阵，交换的两列		*/
/*返回值：无					*/
/*功能：交换矩阵的列			*/
/********************************/
void matrix::swapCol(int c1,int c2)
{
	int i;
	mtype temp;
    c1+=bias;
    c2+=bias;
    for(i=1;i<=row;i++)
	{
        temp=_matrixData_p(this,i,c1);
        _matrixData_p(this,i,c1)=_matrixData_p(this,i,c2);
        _matrixData_p(this,i,c2)=temp;
	}
}

/********************************/
/*函数名：matrixPrint	 		*/
/*参数：待打印矩阵				*/
/*返回值：无					*/
/*功能：打印矩阵				*/
/********************************/
void matrix::matrixPrint(matrix m)
{
	int i,j;
	printf("[");
	for(i=1;i<=m.row;i++)
	{
		for(j=1;j<=m.col;j++)
		{
			printf("%lf",_matrixData(m,i,j));
			if(j!=m.col)
			{
				printf("\t");
			}
		}
		if(i!=m.row)
		{
			printf("\n");
		}
	}
	printf("]\n\n");
}


