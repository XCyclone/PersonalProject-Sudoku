#include "generator.h"

Generator::Generator(int num)
{
	fp = fopen(".\\sudoku.txt", "w+");					//初始化写入文件路径
	this->num = num;									//初始化生成终局个数
	this->now = 0;										//初始化现有终局个数
	//this->start = clock();								//开始时间
	temp[0] = 4;										//根据学号（2+1）%9+1 = 4确定第一位
	generate_first_line(1);								//递归生成第一行
}

void Generator::change_to_num()							//根据模板和第一行生成数列转换为终局
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

void Generator::generate_first_line(int pos)			//递归生成第一行
{
	if (pos == 9)
	{
		for (int i = 1; i < 9; i++)
			if (temp[i] >= 4)	temp[i]++;
		change_to_num();								//根据模板生成终局
		wrap(2);										//对终局的行、列进行交换，由于只需要最大1e6种终局，顾不交换7、8、9行，如需生成超过8709120个终局可改为wrap（1）
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

void Generator::wrap_row(int a, int b)				//交换行a、b
{
	for (int i = 0; i < 9; i++)
	{
		int c = box[a][i];
		box[a][i] = box[b][i];
		box[b][i] = c;
	}
}

void Generator::wrap_col(int a, int b)				//交换列a、b
{
	for (int i = 0; i < 9; i++)
	{
		int c = box[i][a];
		box[i][a] = box[i][b];
		box[i][b] = c;
	}
}

void Generator::wrap(int l)							//将9行(列)分为三组，分别为1、2、3,4、5、6,7、8、9，（由于第一个数字不可改变）在4、5、6和7、8、9中都可随机交换两列使得新终局任满足要求
													//根据递归求解第一行按模板可生成8!=40320终局，在此基础上交换，共可以有8!*3!*3!*3!*3!=52254720种终局
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

void Generator::output()									//输出终局文件
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

	if (this->now == this->num) {								//终止输出时间
		//finish = clock();
		//totaltime = (double)(finish - start) / 1000;
		//cout << "time = " << totaltime << endl;
		exit(0);
	}

}
