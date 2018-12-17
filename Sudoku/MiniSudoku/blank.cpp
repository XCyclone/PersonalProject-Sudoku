#include "blank.h"

Blank::Blank(const char *s)
{
	fp_read = fopen(s, "r+");				//初始化读入文件路径
	fp_write = fopen(".\\block.txt", "w+");
	read_file();
}

void Blank::block_much(int *a)
{
	int n = rand() % 4 + 5;
	while (n--)
	{
		int m = rand() % 9;
		if (m < 3)	*(a + m) = 0;
		else if (m < 6)	*(a + 6 + m) = 0;
		else *(a + 12 + m) = 0;
	}
}

void Blank::block_few(int *a)
{
	int n = rand() % 3 + 2;
	while (n--)
	{
		int m = rand() % 9;
		if (m < 3)	*(a + m) = 0;
		else if (m < 6)	*(a + 6 + m) = 0;
		else *(a + 12 + m) = 0;
	}
}

void Blank::read_file()
{
	while (!feof(fp_read))
	{
		char box_in[170] = { 0 };
		int k = 0;
		fread(box_in, 1, 163, fp_read);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				box[i][j] = box_in[k++] - '0';
				k++;
				//fgetc(fp_read);
				//printf("%d ",box[i][j]);
			}
			//printf("\n");
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if ((i == 0 || i == 2) && (j == 0 || j == 2) || (i == 1 && j == 1))
					block_much(&box[3 * i][3 * j]);
				else	block_few(&box[3 * i][3 * j]);
			}
		output();
	}
}

void Blank::output()
{
	char box_out[170] = { 0 };
	int k = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			box_out[k++] = box[i][j] + '0';
			if (j != 8)	box_out[k++] = ' ';
			//fputc(box[i][j] + '0', fp_write);
			//if (j != 8)	fputc(32, fp_write);
			//if (j == 8)	fprintf(fp_write, "%d", box[i][j]);
			//else fprintf(fp_write, "%d ", box[i][j]);
			//File_G << box[i][j] << " ";
		}
		box_out[k++] = '\n';

		//fputc(10, fp_write);
		//fprintf(fp_write, "\n");
		//File_G << "\n";
	}
	box_out[k++] = '\n';
	box_out[k] = '\0';
	fwrite(box_out, 1, strlen(box_out), fp_write);
}
