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
	//��ȡ�������������
	if (argc > 0)
	{
		//����Ϊ��-c��ʱ�����նˣ���ȡ�����ն���
		if (strcmp(argv[1],"-c") == 0)
		{
			int input;
			sscanf_s(argv[2], "%d", &input);			
			new Generator(input);

		}
		//����Ϊ��-s��ʱ�����������ȡ�����ļ���ַ
		else if (strcmp(argv[1], "-s") == 0)
		{
			const char* input = argv[2];
			cout << input;
			new Solution(input);
		}
	}
	
	return 0;
}