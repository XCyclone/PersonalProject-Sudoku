#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "generator.h"
#include "solution.h"
using namespace std;

int main(int argc, char *argv[])
{
	//获取命令行输入参数
	if (argc > 0)
	{
		//输入为“-c”时生成终端，获取生成终端数
		if (strcmp(argv[1],"-c") == 0)
		{
			int input;
			sscanf_s(argv[2], "%d", &input);			
			new Generator(input);

		}
		//输入为“-s”时求解数独，获取数独文件地址
		else if (strcmp(argv[1], "-s") == 0)
		{
			const char* input = argv[2];
			cout << input;
			new Solution(input);
		}
	}
	
	return 0;
}