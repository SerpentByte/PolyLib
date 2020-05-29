#include <cstdio>

#ifndef XYZ_H
#define XYZ_H
struct xyz
{
	double x, y, z;
	xyz()
	{
		x=0; y=0; z=0;
	}
	xyz(double a,  double b, double c)
	{
		x=a; y=b; z=c;
	}

	/*-------------------------some useful functions*/
	//------------------- simple display
	void display()
	{
		printf("(%.3lf, %.3lf, %.3lf)\n", x, y, z);
		return;
	}

	//------------------- squaring
	void sqr()
	{
		x *= x;
		y *= y;
		z *= z;
	}

	//------------------- summing
	double sum()
	{
		return (x+y+z);
	}

};
#endif