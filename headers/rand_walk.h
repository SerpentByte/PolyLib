#include <iostream>
#include <cmath>
#include "xyz.h"
#include "functions.h"
#include "gromos87_io.h"

using namespace std;

#ifndef RAND_WALK
#define RAND_WALK
/*--------------------------------------------------------------
This function generates a polymer without any
confinement restraints. Self-avoiding has been turned 
on by default but can be switched off by passing a 
false value to the avoid variable. 
If bond = -1, then bond's value is chamged to sig.
mt19937 is a 19937 word 32-bit Mersenne Twister PRNG.
--------------------------------------------------------------*/
xyz *polymer(int n_beads, double sig, bool v, double bond=-1, bool avoid=true)
{
	if(bond==-1)
		bond = sig;
	else if(bond<sig)
	{
		cout<<"ERROR: Bond distance cannot be smaller than particle size.\n";
		return NULL;
	}

	xyz *pol = (xyz*)malloc(sizeof(xyz)*n_beads), pos;
	int num = 1, ctr = 0, pass = 1;
	bool flag = false;
	double dx = 0, dy = 0, dz = 0, sig2 = sig*sig;
	int choice[] = {-1, 0, 1};
	// double bond2 = bond*bond;

	pol[0] = xyz(prng(), prng(), prng());

	while(num<n_beads)
	{
		flag = false;
		if(ctr>1e6)
		{
			if(v)
			{
				xyz *temp = (xyz*)malloc(sizeof(xyz)*num);
				for(int i=0; i<num;i++)
					temp[i] = xyz(pol[i].x, pol[i].y, pol[i].z);

				xyz min, max;

				for(int i=0;i<n_beads;i++)
				{
					//--------------------- finding minimum
					if(min.x>temp[i].x)
						min.x = temp[i].x;
					if(min.y>temp[i].y)
						min.y = temp[i].y;
					if(min.z>temp[i].z)
						min.z = temp[i].z;

					//--------------------- finding maximum
					if(max.x<temp[i].x)
						max.x = temp[i].x;
					if(max.y<temp[i].y)
						max.y = temp[i].y;
					if(max.z<temp[i].z)
						max.z = temp[i].z;
				}

				xyz box = xyz((max.x-min.x), (max.y-min.y), (max.z-min.z));

				string name = "log/rand_pass_"+to_string(pass)+".gro";
				char fname[name.length()];
				strcpy(fname, name.c_str());
				write_gro(fname, temp, num-1,box);
				cout<<"Could not generate in pass-"<<pass<<". ";
				cout<<"Wrote file to rand_pass_"<<pass<<".gro\n";
				free(temp);
			}
			num = 1;
			free(pol);
			pol = (xyz*)malloc(sizeof(xyz)*n_beads);
			pol[0] = xyz(prng(), prng(), prng());
			pos = xyz();
			ctr = 0;
			pass++;
		}
		ctr++;

		/*sign = 1;
		if(prng()<0.5)
			sign = -1;
		
		if(num%2==0)
		{
			dx = prng(-sig/2, sig/2);
			dy = prng(-sig/2, sig/2);
			dz = sig2 - dx*dx - dy*dy;
			dz = sign*sqrt(dz);
		}
		else if(num%3==0)
		{
			dx = prng(-sig/2, sig/2);
			dz = prng(-sig/2, sig/2);
			dy = sig2 - dx*dx - dz*dz;	
			dy = sign*sqrt(dy);
		}
		else
		{
			dy = prng(-sig/2, sig/2);
			dz = prng(-sig/2, sig/2);
			dx = sig2 - dz*dz - dy*dy;
			dx = sign*sqrt(dx);
		}*/

		dx = choice[(int)round(prng(2))]*prng(bond, 1.1*bond);
		dy = choice[(int)round(prng(2))]*prng(bond, 1.1*bond);
		dz = choice[(int)round(prng(2))]*prng(bond, 1.1*bond);

		if((dx*dx+dy*dy+dz*dz)<sig2)
			continue;

		pos = pol[num-1]+xyz(dx,dy,dz);

		if(avoid)
		{
			for(int i=0;i<num;i++)
			{
				if(dist(pos, pol[i])<sig)
				{
					flag = true;
					i=num;
				}
			}
		}

		if(!flag)
		{
			pol[num] = pos;
			num++;
		}
	}

	if(v)
		cout<<"======================================================\n";
	cout<<"Generated polymer in "<<pass<<" passes.\n";

	return pol;		
}
#endif