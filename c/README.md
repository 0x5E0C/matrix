0.具体使用例程在test.c

1.基本设置：
使用前打开matrix.h文件，配置第10行的PROGRAMMER参数、第19行的mtype参数。

2.PROGRAMMER参数说明：
PROGRAMMER为矩阵行列位置使用习惯的设置，可设置为0和1。
0：非程序员模式，矩阵从第1行第1列开始，使用matrixData(m,1,1)取出m矩阵的第1行第1列的数据。
1：程序员模式，矩阵从第0行第0列开始，使用matrixData(m,0,0)取出m矩阵的第1行第1列的数据。

3.mtype参数说明：
mtype为组成矩阵的数据的数据类型，有float和double两种可选参数。

4.注意事项：
（1）矩阵若无手动设置数据，默认都为0.
（2）程序中的矩阵运算没有预先判断运算矩阵是否合理！包括：
	a.矩阵相加减没有判断两个矩阵是否行列相等；
	b.矩阵相乘没有判断第一个矩阵的列是否等于第二个矩阵的行；
	c.行列式运算没有判断矩阵是否为方阵；
	d.求逆矩阵时没有判断逆矩阵是否存在等情况。
（3）只有matrixExtract、swapRow、swapCol的参数关乎PROGRAMMER参数。
（4）使用setMatrix、setDiagonalMatrix时需要传入带小数点的数据，如需要数据1时应写成setMatrix(&m,1.0);
（5）矩阵内存由malloc申请，需要手动free释放内存，所以使用完矩阵后需要使用deleteMatrix或deleteMatrices手动删除矩阵！