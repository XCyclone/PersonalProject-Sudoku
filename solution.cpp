#include "solution.h"

Solution::Solution(const char* s)
{
	fp_read = fopen(s, "r+");				//初始化读入文件路径
	fp_write = fopen(".\\sudoku.txt", "w+");			//初始化写入文件路径
	//this->start = clock();								//开始时间
	read_file();										//读取文件
	//finish = clock();
	//totaltime = (double)(finish - start) / 1000;		//结束时输出时间
	//cout << "time = " << totaltime << endl;
	exit(0);
}

void Solution::read_file()								//读入文件，将文件存入数组
{
	while (!feof(fp_read))
	{
		char box_in[170] = { 0 };
		int k = 0;
		fread(box_in, 1, 162, fp_read);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				box[i][j] = box_in[k++] - '0';
				k++;

			}
		}
		fread(box_in, 1, 1, fp_read);
		full();											//填充空格
	}
}

void Solution::full()									//填充空格：通过扫描查看每个空目前可以填充的数字，如果唯一则填入
{
	flag = 1;
	int block_num = 0;
	while (flag)										//只要每次扫描都有新的可填入位置，则不断扫描，知道一次扫描不再可以填入新数字
	{
		flag2 = 0;
		for (int i = 0; i < 9; i++) 
		{
			for (int j = 0; j < 9; j++)
			{
				if (box[i][j] == 0)	full_block(i, j);
			}
		}
		flag = flag2;
	}
	int block_m, block_n, f = 0;
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++)
		{
			if (box[i][j] == 0) {
				block_num++;
				if (f == 0) {
					block_m = i;
					block_n = j;
					f = 1;
				}
			}
		}
	}
	if (block_num)	full_dfs(block_m, block_n);			//当扫描法结束后仍然有空位存在，则解不唯一，进行递归求解
	output();
}

void Solution::full_block(int m, int n)					//填充某空格：通过对行、列、3*3矩阵的扫描确定可以填入的数组，如果唯一则马上填入，不唯一则等待下次扫描
{
	int check[10] = { 0 };
	int k = 9 * m + n;
	int f = 0;
	for (int i = 0; i < 9; i++)	
		if(box[i][n] != 0)	check[box[i][n]] = 1;
	for (int i = 0; i < 9; i++) 
		if (box[m][i] != 0)	check[box[m][i]] = 1;
	for (int i = 3 * (m / 3); i < 3 * (m / 3) + 3; i++) 
	{
		for (int j = 3 * (n / 3); j < 3 * (n / 3) + 3; j++)
		{
			if (box[i][j] != 0)	check[box[i][j]] = 1;
		}
	}
	for (int j = 1; j < 10; j++)
	{
		if (check[j] == 0 && f != 0)	f = -1;
		else if (check[j] == 0)	f = j;
	}
	if (f > 0)
	{
		box[m][n] = f;
		flag2 = 1;
	}
}

bool Solution::find_next_block(int now_row, int *row, int *col)		//寻找下一空格
{
	int i, j;
	for (i = now_row; i < 9; i++)
		for (j = 0; j < 9; j++)
			if (box[i][j] == 0)
			{
				*row = i;
				*col = j;
				return true;
			}
	return false;
}

bool Solution::full_dfs(int row, int col)						//递归求解剩余空格（此时求解空格较少，速度较快）
{
	int i, j, n;
	int next_row, next_col;
	n = 0;
	while (1) {
	next_num:
		n++;
		if (n >= 10) break;
		for (j = 0; j < 9; j++) {								// 判断行是否有重复
			if (box[row][j] == n) {
				goto next_num;
			}
		}
		for (i = 0; i < 9; i++) {								// 判断列是否重复
			if (box[i][col] == n) {
				goto next_num;
			}
		}
		for (i = 3 * (row / 3); i < 3 * (row / 3) + 3; i++) {				//判断所在3*3矩阵是否有重复
			for (j = 3 * (col / 3); j < 3 * (col / 3) + 3; j++) {
				if (box[i][j] == n) {
					goto next_num;
				}
			}
		}
		box[row][col] = n;										//当该单元可以填充
		if (!find_next_block(row, &next_row, &next_col)) {		//填满，则找到可行解
			return true;
		}
		if (!full_dfs(next_row, next_col)) {					//否则继续填下一个未填充的空
			box[row][col] = 0;
			continue;
		}
		else
			return true;
	}
	return false;
}


void Solution::output()										//输出到文件
{
	char box_out[170] = { 0 };
	int k = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			box_out[k++] = box[i][j] + '0';
			if (j != 8)	box_out[k++] = ' ';
		}
		box_out[k++] = '\n';

	}
	if(!feof(fp_read))	box_out[k++] = '\n';
	box_out[k] = '\0';
	fwrite(box_out, 1, strlen(box_out), fp_write);

}
