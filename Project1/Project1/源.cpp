#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "generator.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc > 0)
	{
		//cout << argv[1] << endl;
		if (strcmp(argv[1],"-c") == 0)
		{
			int input;
			sscanf_s(argv[2], "%d", &input);			
			new Generator(input);

		}
		else if(strcmp(argv[1], "-s") == 0)
			cout << "sorry" << endl;
	}
	
	return 0;
}