#include <random>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <cstring>
#include "xyz.h"

using namespace std;

#ifndef FUNC_H
#define FUNC_H
/*-------------------------------------------------------------
This is a random number generator. It used Mersenne Twister
32-bit to generate random numbers between a and b.
-------------------------------------------------------------*/
double prng(double a, double b)
{
	mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
	double r = (double)generator()/generator.max();
	// srand(chrono::system_clock::now().time_since_epoch().count());
	// double r = (float)rand()/RAND_MAX;
	r *= (b-a);
	r += a;

	return r;
}

/*-------------------------------------------------------------
This is a random number generator. It used Mersenne Twister
32-bit to generate random numbers between 0 and b.
-------------------------------------------------------------*/
double prng(double b)
{
	mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
	double r = (double)generator()/generator.max();
	// srand(chrono::system_clock::now().time_since_epoch().count());
	// double r = (float)rand()/RAND_MAX;
	r *= b;

	return r;
}

/*-------------------------------------------------------------
This is a random number generator. It used Mersenne Twister
32-bit to generate random numbers between 0 and 1.
-------------------------------------------------------------*/
double prng()
{
	mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
	double r = (double)generator()/generator.max();
	// srand(chrono::system_clock::now().time_since_epoch().count());
	// double r = (float)rand()/RAND_MAX;

	return r;
}

/*-------------------------------------------------------------
operator overloading for xyz
-------------------------------------------------------------*/
//------------------------------addition
xyz operator +(xyz v1, xyz v2 )
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

//------------------------------subtraction
xyz operator -(xyz v1, xyz v2 )
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}
//------------------------------element-wise multiplication
xyz operator *(xyz v1, xyz v2 )
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return v1;
}
xyz operator *(xyz v1, double n )
{
	v1.x *= n;
	v1.y *= n;
	v1.z *= n;
	return v1;
}
xyz operator *(xyz v1, int n )
{
	v1.x *= n;
	v1.y *= n;
	v1.z *= n;
	return v1;
}
xyz operator *(double n, xyz v1)
{
	v1.x *= n;
	v1.y *= n;
	v1.z *= n;
	return v1;
}
xyz operator *(int n, xyz v1)
{
	v1.x *= n;
	v1.y *= n;
	v1.z *= n;
	return v1;
}
//------------------------------element-wise division
xyz operator /(xyz v1, xyz v2 )
{
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	return v1;
}
xyz operator /(xyz v1, double n )
{
	v1.x /= n;
	v1.y /= n;
	v1.z /= n;
	return v1;
}
xyz operator /(xyz v1, int n )
{
	v1.x /= n;
	v1.y /= n;
	v1.z /= n;
	return v1;
}
xyz operator /(double n, xyz v1)
{
	v1.x /= n;
	v1.y /= n;
	v1.z /= n;
	return v1;
}
xyz operator /(int n, xyz v1)
{
	v1.x /= n;
	v1.y /= n;
	v1.z /= n;
	return v1;
}

/*--------------------------------------------------------------
This function calculates dot product
--------------------------------------------------------------*/
double dot(xyz v1, xyz v2)
{
	return (v1*v2).sum();
}

/*--------------------------------------------------------------
This function calculates distance between two vectors
--------------------------------------------------------------*/
inline double dist(xyz v1, xyz v2)
{
	xyz v = v1-v2;
	v.sqr();
	return sqrt(v.sum());
}

/*--------------------------------------------------------------
This function checks for overlaps between beads of a polymer
--------------------------------------------------------------*/
bool overlap(int n_beads, xyz *pol, double sig)
{
	for(int i=0;i<n_beads;i++)
	{
		
		for(int j=i+1;j<n_beads;j++)
		{
			if(dist(pol[i], pol[j])<sig)
			{
				return true;
			}
		}
	}

	return false;
}

/*--------------------------------------------------------------
Convert a string to lowercase
--------------------------------------------------------------*/
string toLower(string s)
{
	for(int i=0;i<s.length();i++)
	{
		s[i] = tolower(s[i]);
	}

	return s;
}
#endif