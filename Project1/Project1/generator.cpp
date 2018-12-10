#include "generator.h"
#include <windows.h>

int box[9][9] = { 0 };
int temp[9] = { 0 };
int mark[9] = { 0 };
char model[9][9] = {
		{ 'i','g','h','c','a','b','f','d','e' },{ 'c','a','b','f','d','e','i','g','h' },{ 'f','d','e','i','g','h','c','a','b' },{ 'g','h','i','a','b','c','d','e','f' },{ 'a','b','c','d','e','f','g','h','i' },{ 'd','e','f','g','h','i','a','b','c' },{ 'h','i','g','b','c','a','e','f','d' },

	{ 'b','c','a','e','f','d','h','i','g' },{ 'e','f','d','h','i','g','b','c','a' }
};

FILE *fp = NULL;
ofstream File_G(".\\sudoku.txt");

Generator::Generator(int num)
{	
	fp = fopen(".\\sudoku.txt", "wb+");
	this->num = num;
	this->now = 0;
	this->start = clock();
	temp[0] = 4;
	generate_first_line(1);
}

void Generator::change_to_num()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (model[i][j] == 'a') box[i][j] = temp[8];
			else if (model[i][j] == 'b') box[i][j] = temp[1];
			else if (model[i][j] == 'c') box[i][j] = temp[2];
			else if (model[i][j] == 'd') box[i][j] = temp[3];
			else if (model[i][j] == 'e') box[i][j] = temp[4];
			else if (model[i][j] == 'f') box[i][j] = temp[5];
			else if (model[i][j] == 'g') box[i][j] = temp[6];
			else if (model[i][j] == 'h') box[i][j] = temp[7];
			else if (model[i][j] == 'i') box[i][j] = temp[0];
		}
	}
}

void Generator::generate_first_line(int pos)
{
	if (pos == 9)
	{
		for (int i = 1; i < 9; i++)
			if (temp[i] >= 4)	temp[i]++;
		change_to_num();
		wrap(2);
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

void Generator::wrap_row(int a, int b)
{
	for (int i = 0; i < 9; i++)
	{
		int c = box[a][i];
		box[a][i] = box[b][i];
		box[b][i] = c;
	}
}

void Generator::wrap_col(int a, int b)
{
	for (int i = 0; i < 9; i++)
	{
		int c = box[i][a];
		box[i][a] = box[i][b];
		box[i][b] = c;
	}
}


void Generator::wrap(int l)
{
	if (l == 4)
	{
		if (now == num)	exit(0);
		//if(now != num)
			output();
		//else return;
		wrap_col(6, 7);
		//if (now != num)
			output();
		//else return;
		wrap_col(7, 8);
		//if (now != num)
			output();
		//else return;
		wrap_col(6, 8);
		//if (now != num)
			output();
		//else return;
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
		//wrap_col(3, 4);
		wrap_col(4, 5);
		wrap(l + 1);
		//wrap_col(3, 5);
		wrap_col(3, 5);
		wrap(l + 1);
		//wrap_col(4, 5);
		wrap_col(3, 4);
		wrap(l + 1);
		//wrap_col(3, 4);
		wrap_col(4, 5);
		wrap(l + 1);
		//wrap_col(3, 5);
		wrap_col(3, 5);
	}
	if (l == 2)
	{
		wrap(l + 1);
		wrap_row(3, 4);
		wrap(l + 1);
		//	wrap_row(3,4);
		wrap_row(4, 5);
		wrap(l + 1);
		//	wrap_row(3,5);
		wrap_row(3, 5);
		wrap(l + 1);
		//	wrap_row(4,5);
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
		//	wrap_row(6,7);
		wrap_row(7, 8);
		wrap(l + 1);
		//	wrap_row(6,8);
		wrap_row(6, 8);
		wrap(l + 1);
		//	wrap_row(7,8);
		wrap_row(6, 7);
		wrap(l + 1);
		wrap_row(7, 8);
		wrap(l + 1);
		wrap_row(6, 8);
	}
}

void Generator::output()
{
	now++;
	//fwrite(box, sizeof(box), 81, fp);
	//fclose(fp);
	for(int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			fprintf(fp, "%c ", box[i][j]);
			//File_G << box[i][j] << " ";
		}
		fprintf(fp, "\n");
		//File_G << "\n";
	}
	//File_G << "\n";
	if (this->now == this->num) {
		finish = clock();
		totaltime = (double)(finish - start) / 1000;
		cout << "time = " << totaltime << endl;
		exit(0);
	}
		
}
