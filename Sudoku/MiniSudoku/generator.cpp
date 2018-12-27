#include "generator.h"

Generator::Generator(int num)
{
	fp = fopen(".\\sudoku.txt", "w+");					//��ʼ��д���ļ�·��
	this->num = num;									//��ʼ�������վָ���
	this->now = 0;										//��ʼ�������վָ���
	//this->start = clock();								//��ʼʱ��
	temp[0] = 4;										//����ѧ�ţ�2+1��%9+1 = 4ȷ����һλ
	generate_first_line(1);								//�ݹ����ɵ�һ��
}

void Generator::change_to_num()							//����ģ��͵�һ����������ת��Ϊ�վ�
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (model[i][j] == 'i') box[i][j] = temp[0];
			else if (model[i][j] == 'g') box[i][j] = temp[1];			
			else if (model[i][j] == 'h') box[i][j] = temp[2];
			else if (model[i][j] == 'c') box[i][j] = temp[3];
			else if (model[i][j] == 'a') box[i][j] = temp[4];
			else if (model[i][j] == 'b') box[i][j] = temp[5];
			else if (model[i][j] == 'f') box[i][j] = temp[6];
			else if (model[i][j] == 'd') box[i][j] = temp[7];
			else if (model[i][j] == 'e') box[i][j] = temp[8];
		}
	}
}

void Generator::generate_first_line(int pos)			//�ݹ����ɵ�һ��
{
	if (pos == 9)
	{
		for (int i = 1; i < 9; i++)
			if (temp[i] >= 4)	temp[i]++;
		change_to_num();								//����ģ�������վ�
		wrap(2);										//���վֵ��С��н��н���������ֻ��Ҫ���1e6���վ֣��˲�����7��8��9�У��������ɳ���8709120���վֿɸ�Ϊwrap��1��
		for (int i = 1; i < 9; i++)
			if (temp[i] >= 4)	temp[i]--;
		return;
	}
	for (int i = 1; i < 9; i++)
	{
		if (mark[i] == 0)
		{
			temp[pos] = i;
			mark[i] = 1;
			generate_first_line(pos + 1);
			temp[pos] = 0;
			mark[i] = 0;
		}
	}
}

void Generator::wrap_row(int a, int b)				//������a��b
{
	for (int i = 0; i < 9; i++)
	{
		int c = box[a][i];
		box[a][i] = box[b][i];
		box[b][i] = c;
	}
}

void Generator::wrap_col(int a, int b)				//������a��b
{
	for (int i = 0; i < 9; i++)
	{
		int c = box[i][a];
		box[i][a] = box[i][b];
		box[i][b] = c;
	}
}

void Generator::wrap(int l)							//��9��(��)��Ϊ���飬�ֱ�Ϊ1��2��3,4��5��6,7��8��9�������ڵ�һ�����ֲ��ɸı䣩��4��5��6��7��8��9�ж��������������ʹ�����վ�������Ҫ��
													//���ݵݹ�����һ�а�ģ�������8!=40320�վ֣��ڴ˻����Ͻ�������������8!*3!*3!*3!*3!=52254720���վ�
{
	if (l == 4)
	{
		if (now == num)	exit(0);
		output();
		wrap_col(6, 7);
		output();
		wrap_col(7, 8);
		output();
		wrap_col(6, 8);
		output();
		wrap_col(6, 7);
		output();
		wrap_col(7, 8);
		output();
		wrap_col(6, 8);
		return;
	}
	if (l == 3)
	{
		wrap(l + 1);
		wrap_col(3, 4);
		wrap(l + 1);
		wrap_col(4, 5);
		wrap(l + 1);
		wrap_col(3, 5);
		wrap(l + 1);
		wrap_col(3, 4);
		wrap(l + 1);
		wrap_col(4, 5);
		wrap(l + 1);
		wrap_col(3, 5);
	}
	if (l == 2)
	{
		wrap(l + 1);
		wrap_row(3, 4);
		wrap(l + 1);
		wrap_row(4, 5);
		wrap(l + 1);
		wrap_row(3, 5);
		wrap(l + 1);
		wrap_row(3, 4);
		wrap(l + 1);
		wrap_row(4, 5);
		wrap(l + 1);
		wrap_row(3, 5);
	}
	if (l == 1)
	{
		wrap(l + 1);
		wrap_row(6, 7);
		wrap(l + 1);
		wrap_row(7, 8);
		wrap(l + 1);
		wrap_row(6, 8);
		wrap(l + 1);
		wrap_row(6, 7);
		wrap(l + 1);
		wrap_row(7, 8);
		wrap(l + 1);
		wrap_row(6, 8);
	}
}

void Generator::output()									//����վ��ļ�
{
	now++;
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
	if (this->now != this->num)	box_out[k++] = '\n';
	box_out[k] = '\0';
	fwrite(box_out, 1, strlen(box_out), fp);

	if (this->now == this->num) {								//��ֹ���ʱ��
		//finish = clock();
		//totaltime = (double)(finish - start) / 1000;
		//cout << "time = " << totaltime << endl;
		exit(0);
	}

}
