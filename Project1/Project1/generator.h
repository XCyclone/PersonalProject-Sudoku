#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <cstring>

using namespace std;

class Generator
{
private:
	int num = 0;
	int now = 0;
	clock_t start, finish;
	double totaltime;

public:
	Generator(int);
	void change_to_num();
	void generate_first_line(int );
	void wrap_row(int, int);
	void wrap_col(int, int);
	void wrap(int);
	void output();

};



#endif // !1