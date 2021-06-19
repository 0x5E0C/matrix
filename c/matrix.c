#include "matrix.h"

/*********************************/
//函数名：createMatrix 
//参数：矩阵的行大小，列大小
//返回值：创建的矩阵     
//功能：创建指定大小的矩阵   
/********************************/
matrix createMatrix(int row,int col)
{
	matrix m;
	m.row=row;
	m.col=col;
	m.data=(mtype*)malloc(row*col*sizeof(mtype));
	memset(m.data,0,row*col*sizeof(mtype));
	return m;
}

/********************************/
//函数名：createIdentityMatrix  
//参数：矩阵的阶数              
//返回值：创建的矩阵           
//功能：创建指定阶数的单位矩阵 
/********************************/
matrix createIdentityMatrix(int order)
{
	int i;
	matrix m;
	m.row=order;
	m.col=order;
	m.data=(mtype*)malloc(order*order*sizeof(mtype));
	memset(m.data,0,order*order*sizeof(mtype));
	for(i=1;i<=order;i++)
	{
		_matrixData(m,i,i)=1;
	}
	return m;
}

/********************************/
//函数名：deleteMatrix      
//参数：矩阵的指针             
//返回值：无                     
//功能：释放该矩阵申请的内存	    
/********************************/
void deleteMatrix(matrix *m)
{
    free(m->data);
}

/****************************************/
//函数名：deleteMatrices               
//参数：矩阵列表的指针               
//返回值：无	                       
//功能：释放该矩阵列表内的矩阵申请的内存
/****************************************/
void deleteMatrices(matrix *m[],int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        deleteMatrix(m[i]);
    }
}

/********************************/
//函数名：copyMatrix     
//参数：待拷贝矩阵              
//返回值：拷贝出的矩阵         
//功能：拷贝矩阵               
/********************************/
matrix copyMatrix(matrix m)
{
	matrix a=createMatrix(m.row,m.col);
	memcpy(a.data,m.data,m.row*m.col*sizeof(mtype));
	return a;
}

/********************************/
//函数名：setMatrix             
//参数：待赋值矩阵，赋值数据	   
//返回值：无	                  
//功能：给矩阵赋值              
/********************************/
void setMatrix(matrix *m,mtype arg1,...)
{
	va_list valist;
    int i;
    va_start(valist,arg1);
    *(m->data)=arg1;
    for(i=1;i<m->row*m->col;i++)
    {
       *(m->data+i)=va_arg(valist,double);
    }
    va_end(valist);
}

/********************************/
//函数名：setDiagonalMatrix    
//参数：待赋值矩阵，赋值数据	  
//返回值：无	                   
//功能：给矩阵的对角线赋值     
/********************************/
void setDiagonalMatrix(matrix *m,mtype arg1,...)
{
	va_list valist;
    int i;
    va_start(valist,arg1);
    *(m->data)=arg1;
    for(i=2;i<=m->row;i++)
    {
       _matrixData_p(m,i,i)=va_arg(valist,double);
    }
    va_end(valist);
}

/********************************/
//函数名：matrixAdd            
//参数：相加的两个矩阵          
//返回值：相加结果              
//功能：矩阵相加              
/********************************/
matrix matrixAdd(matrix a,matrix b)
{
	int i,j;
	matrix m=createMatrix(a.row,a.col);
	for(i=1;i<=a.row;i++)
	{
		for(j=1;j<=a.col;j++)
		{
			_matrixData(m,i,j)=_matrixData(a,i,j)+_matrixData(b,i,j);
		}
	}
	return m;
}

/********************************/
//函数名：matrixSub            
//参数：相减的两个矩阵          
//返回值：相减结果               
//功能：矩阵相减                 
/********************************/
matrix matrixSub(matrix a,matrix b)
{
	int i,j;
	matrix m=createMatrix(a.row,a.col);
	for(i=1;i<=a.row;i++)
	{
		for(j=1;j<=a.col;j++)
		{
			_matrixData(m,i,j)=_matrixData(a,i,j)-_matrixData(b,i,j);
		}
	}
	return m;
}

/********************************/
//函数名：matrixMul        
//参数：相乘的两个矩阵         
//返回值：相乘结果             
//功能：矩阵相乘               
/********************************/
matrix matrixMul(matrix a,matrix b)
{
    int i,j,k;
	matrix m=createMatrix(a.row,b.col);
	for(i=1;i<=a.row;i++)
	{
		for(j=1;j<=b.col;j++)
		{
			for(k=1;k<=a.col;k++)
			{
				_matrixData(m,i,j)+=_matrixData(a,i,k)*_matrixData(b,k,j);
			}
		}
	}
	return m;
}

/********************************/
//函数名：matrixScalarMul       
//参数：乘数，矩阵              
//返回值：相乘结果            
//功能：矩阵数乘               
/********************************/
matrix matrixScalarMul(mtype a,matrix b)
{
	int i,j;
	matrix m=createMatrix(b.row,b.col);
	for(i=1;i<=b.row;i++)
	{
		for(j=1;j<=b.col;j++)
		{
			_matrixData(m,i,j)=a*_matrixData(b,i,j);
		}
	}
	return m;
}

/********************************/
//函数名：matrixTrans            
//参数：待转置矩阵              
//返回值：转置结果               
//功能：矩阵转置              
/********************************/
matrix matrixTrans(matrix a)
{
	int i,j;
	matrix m=createMatrix(a.col,a.row);
	for(i=1;i<=a.row;i++)
	{
		for(j=1;j<=a.col;j++)
		{
			_matrixData(m,j,i)=_matrixData(a,i,j);
		}
	}
	return m;
}

/********************************/
//函数名：matrixDet	            
//参数：待求行列式的矩阵        
//返回值：行列式的结果       
//功能：求矩阵的行列式        
/********************************/
mtype matrixDet(matrix t)
{
	matrix m=copyMatrix(t);
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
                        swapRow(&m,a-1,b);
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
//函数名：matrixInv	            
//参数：待求逆的矩阵         
//返回值：逆矩阵               
//功能：求矩阵的逆矩阵          
/********************************/
matrix matrixInv(matrix a)
{
    int i,j,l;
	int order=a.row;
    double mul;
	matrix result=createMatrix(a.row,a.col);
	matrix t=createIdentityMatrix(a.row);
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
    result=matrixExtract(m,1-bias,order+1-bias,order-bias,2*order-bias);
    deleteMatrix(&t);
    deleteMatrix(&m);
	return result;
}

/********************************************************/
//函数名：matrixMerge                               
//参数：待合并的两个矩阵，方向（r：右合并，b：下合并）
//返回值：合并后的矩阵                                 
//功能：合并矩阵                                       
/********************************************************/
matrix matrixMerge(matrix a,matrix b,char dir)
{
	int i,j;
	matrix m;
	if(dir=='r')
	{
		m=createMatrix(a.row,a.col+b.col);
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
	}
	else if(dir=='b')
	{
		m=createMatrix(a.row+b.row,a.col);
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
	}
	return m;
}

/****************************************************/
//函数名：matrixExtract                            
//参数：待截取矩阵，开始截取的行，列，结束的行，列   
//返回值：逆矩阵                                  
//功能：求矩阵的逆矩阵                            
/****************************************************/
matrix matrixExtract(matrix a,int t,int l,int b,int r)
{
	int i,j;
	matrix m=createMatrix(b-t+1,r-l+1);
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
//函数名：swapRow               
//参数：矩阵，交换的两行        
//返回值：无                    
//功能：交换矩阵的行            
/********************************/
void swapRow(matrix *m,int r1,int r2)
{
	int i;
	mtype temp;
    r1+=bias;
    r2+=bias;
	for(i=1;i<=m->col;i++)
	{
        temp=_matrixData_p(m,r1,i);
        _matrixData_p(m,r1,i)=_matrixData_p(m,r2,i);
        _matrixData_p(m,r2,i)=temp;
	}
}

/********************************/
//函数名：swapCol                
//参数：矩阵，交换的两列        
//返回值：无	                   
//功能：交换矩阵的列             
/********************************/
void swapCol(matrix *m,int c1,int c2)
{
	int i;
	mtype temp;
    c1+=bias;
    c2+=bias;
	for(i=1;i<=m->row;i++)
	{
		temp=_matrixData_p(m,i,c1);
		_matrixData_p(m,i,c1)=_matrixData_p(m,i,c2);
		_matrixData_p(m,i,c2)=temp;
	}
}

/********************************/
//函数名：matrixPrint          
//参数：待打印矩阵            
//返回值：无	                
//功能：打印矩阵            
/********************************/
void matrixPrint(matrix m)
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

