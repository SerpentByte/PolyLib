#include <iostream>
#include <cmath>
#include <omp.h>
#include "xyz.h"
#include "functions.h"
#include "gromos87_io.h"

using namespace std;

#ifndef BOX
#define BOX

#define PI 4*atan(1.0)

/*--------------------------------------------------------------
This generates a polymer inside a box
---------------------------------------------------------------*/
xyz *boxed(int n_beads, double sig, xyz box, xyz centre,
	bool v, double bond=-1,	bool avoid=true, 
	int n_threads=omp_get_max_threads())
{
	if(bond==-1)
		bond = sig;
	else if(sig>bond)
	{
		cout<<"ERROR: sigma greater than provided bond distance.\n";
		return NULL;
	}
	/*-------------------------------
	checking whether polymer can be
	genrated inside the confinement.
	-------------------------------*/
	double vol_box = box.x*box.y*box.z;
	double vol_pol = 4*n_beads*PI*pow(sig/2,3)/3;
	if(v)
		printf("Packing fraction = %.3lf\n", (vol_pol/vol_box));
	if(vol_pol/vol_box>0.95)
	{
		cout<<"packing fraction > 0.95. Cannot generate.\n";
		return NULL;
	}
	//-------------------------------


	xyz *pol = (xyz*)malloc(sizeof(xyz)*n_beads), pos;
	int num = 1, ctr = 0, pass = 1;
	bool flag = false;
	double dx = 0, dy = 0, dz = 0, sig2 = sig*sig;
	//double bond2 = bond*bond;
	double prop=0;
	int choice[] = {-1, 0, 1};

	pol[0] = xyz(prng(-box.x/2,box.x/2), prng(-box.y/2,box.y/2), 
				prng(-box.z/2, box.z/2));

	while(num<n_beads)
	{
		flag = false;
		if(ctr>1e6)
		{
			if(v)
			{
				xyz *temp = (xyz*)malloc(sizeof(xyz)*num);
				for(int i=0; i<num;i++)
					temp[i] = xyz(pol[i].x, pol[i].y, pol[i].z)+centre;
				string name = "box_pass_"+to_string(pass)+".gro";
				char fname[name.length()];
				strcpy(fname, name.c_str());
				write_gro(fname, temp, num-1, box);
				cout<<"Could not generate in pass-"<<pass<<". ";
				cout<<"Wrote file to box_pass_"<<pass<<".gro\n";
				free(temp);
			}
			num = 1;
			free(pol);
			pol = (xyz*)malloc(sizeof(xyz)*n_beads);
			pol[0] = xyz(prng(-box.x/2,box.x/2), prng(-box.y/2,box.y/2), 
				prng(-box.z/2, box.z/2));
			pos = xyz();
			ctr = 0;
			pass++;
		}
		ctr++;

		// sign = 1;
		// if(prng()<0.5)
		// 	sign = -1;
		
		/*if(num%2==0)
		{
			dx = prng(-sig/2, sig/2);
			dy = prng(-sig/2, sig/2);
			dz = bond2 - dx*dx - dy*dy;
			dz = sign*sqrt(dz);
		}
		else if(num%3==0)
		{
			dx = prng(-sig/2, sig/2);
			dz = prng(-sig/2, sig/2);
			dy = bond2 - dx*dx - dz*dz;	
			dy = sign*sqrt(dy);
		}
		else
		{
			dy = prng(-sig/2, sig/2);
			dz = prng(-sig/2, sig/2);
			dx = bond2 - dz*dz - dy*dy;
			dx = sign*sqrt(dx);
		}*/

		dx = choice[(int)round(prng(2))]*prng(bond, 1.1*bond);
		dy = choice[(int)round(prng(2))]*prng(bond, 1.1*bond);
		// dz = bond2 - dx*dx - dy*dy;
		// dz = sign*sqrt(dz);
		dz = choice[(int)round(prng(2))]*prng(bond, 1.1*bond);


		if((dx*dx+dy*dy+dz*dz)<sig2)
		{
			continue;
		}	

		pos = pol[num-1]+xyz(dx,dy,dz);

		if(abs(pos.x)>=box.x/2 || abs(pos.y)>=box.y/2 || abs(pos.z)>=box.z/2)
		{
			continue;
		}

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

	omp_set_num_threads(n_threads);

	#pragma omp parallel for
	for(int i=0; i<n_beads;i++)
	{
		pol[i] = pol[i]+centre;
	}

	if(v)
		cout<<"======================================================\n";
	cout<<"Generated polymer in "<<pass<<" passes. ";
	printf("Packing fraction= %.3lf\n",(vol_pol/vol_box));

	return pol;		
}
#endif