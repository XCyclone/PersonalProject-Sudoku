#include "solution.h"

Solution::Solution(const char* s)
{
	fp_read = fopen(s, "r+");				//��ʼ�������ļ�·��
	fp_write = fopen(".\\sudoku.txt", "w+");			//��ʼ��д���ļ�·��
	//this->start = clock();								//��ʼʱ��
	read_file();										//��ȡ�ļ�
	//finish = clock();
	//totaltime = (double)(finish - start) / 1000;		//����ʱ���ʱ��
	//cout << "time = " << totaltime << endl;
	exit(0);
}

void Solution::read_file()								//�����ļ������ļ���������
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
		full();											//���ո�
	}
}

void Solution::full()									//���ո�ͨ��ɨ��鿴ÿ����Ŀǰ�����������֣����Ψһ������
{
	flag = 1;
	int block_num = 0;
	while (flag)										//ֻҪÿ��ɨ�趼���µĿ�����λ�ã��򲻶�ɨ�裬֪��һ��ɨ�費�ٿ�������������
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
	if (block_num)	full_dfs(block_m, block_n);			//��ɨ�跨��������Ȼ�п�λ���ڣ���ⲻΨһ�����еݹ����
	output();
}

void Solution::full_block(int m, int n)					//���ĳ�ո�ͨ�����С��С�3*3�����ɨ��ȷ��������������飬���Ψһ���������룬��Ψһ��ȴ��´�ɨ��
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

bool Solution::find_next_block(int now_row, int *row, int *col)		//Ѱ����һ�ո�
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

bool Solution::full_dfs(int row, int col)						//�ݹ����ʣ��ո񣨴�ʱ���ո���٣��ٶȽϿ죩
{
	int i, j, n;
	int next_row, next_col;
	n = 0;
	while (1) {
	next_num:
		n++;
		if (n >= 10) break;
		for (j = 0; j < 9; j++) {								// �ж����Ƿ����ظ�
			if (box[row][j] == n) {
				goto next_num;
			}
		}
		for (i = 0; i < 9; i++) {								// �ж����Ƿ��ظ�
			if (box[i][col] == n) {
				goto next_num;
			}
		}
		for (i = 3 * (row / 3); i < 3 * (row / 3) + 3; i++) {				//�ж�����3*3�����Ƿ����ظ�
			for (j = 3 * (col / 3); j < 3 * (col / 3) + 3; j++) {
				if (box[i][j] == n) {
					goto next_num;
				}
			}
		}
		box[row][col] = n;										//���õ�Ԫ�������
		if (!find_next_block(row, &next_row, &next_col)) {		//���������ҵ����н�
			return true;
		}
		if (!full_dfs(next_row, next_col)) {					//�����������һ��δ���Ŀ�
			box[row][col] = 0;
			continue;
		}
		else
			return true;
	}
	return false;
}


void Solution::output()										//������ļ�
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
