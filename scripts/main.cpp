#include<iostream>
#include<cstring>
// #include "../headers/gromos87_io.h"
// #include "../headers/genpol.h"
// #include "../headers/xyz.h"
#include "../headers/functions.h"

int main(int argc, char* args[])
{
	/*
	xyz *pos, box;

	box = xyz(138.5, 138.5, 368.84);
	int n_beads = 928, nt=1;
	double sig = 1, rad=10,  l=20;
	xyz centre = xyz();
	bool avoid = true,  cen_val=false, verbose=false;
	string opt_flag = "";
	int confine=0;

	/*-----------------------------------
	|			Argument parser			|
	-----------------------------------*/

	/*for(int i=1;i<argc;i++)
	{
		opt_flag = args[i];

		if(!opt_flag.compare("-beads"))
			n_beads = atoi(args[i+1]);
		else if(!opt_flag.compare("-nt"))
			nt = atoi(args[i+1]);
		else if(!opt_flag.compare("-sig"))
			sig = atof(args[i+1]);
		else if(!opt_flag.compare("-avoid"))
		{
			opt_flag = toLower(args[i+1]);
			if(!opt_flag.compare("false"))
				avoid = false;
		}
		else if(!opt_flag.compare("-rad"))
			rad = atof(args[i+1]);
		else if(!opt_flag.compare("-centre"))
		{
			centre = xyz(atof(args[i+1]),
				atof(args[i+2]),atof(args[i+3]));
		}
		else if(!opt_flag.compare("-l"))
			l = atof(args[i+1]);
		else if(!opt_flag.compare("-box"))
		{
			box = xyz(atof(args[i+1]),
				atof(args[i+2]),atof(args[i+3]));
		}
		else if(!opt_flag.compare("-c"))
			cen_val=true;
		else if(!opt_flag.compare("-confine"))
		{
			opt_flag = args[i+1];
			if(!opt_flag.compare("none"))
				confine = 0;
			else if(!opt_flag.compare("box"))
				confine = 1;
			else if(!opt_flag.compare("sph"))
				confine = 2;
			else if(!opt_flag.compare("spcl"))
				confine = 3;
		}
		else if(!opt_flag.compare("-v"))
			verbose = true;
	}
	if(cen_val)
	{
		centre = box/2;
	}

	if(verbose)
	{
		printf("Beads=%d\nsigma=%.3lf\nradius=%.3lf\nlength=%.3lf\navoid=%d\nnt=%d\n", 
			n_beads, sig, rad, l, avoid, nt);
		cout<<"Centre="; centre.display();
		cout<<"Box="; box.display();
		cout<<"Confinement= "<<confine<<endl;
		cout<<"---------------------------------------\n";
	}

	switch(confine)
	{
		case 0:
			pos = polymer(n_beads, sig, -1);
			break;
		case 1:
			pos = boxed(n_beads, sig, -1, box);
			break;
		case 2:
			pos = spherical(n_beads, sig, -1, rad, centre);
			box = xyz(2*rad, 2*rad, 2*rad);
			centre = box/2;
			break;
		case 3:
			pos = spherocylinder(n_beads, sig, -1, rad, l, centre);
			break;
		default:
			cout<<"Incorrect option.\n";
			exit(0);
	}

	if(pos!=NULL)
	{
		if(overlap(n_beads, pos, sig))
			cout<<"Overlap detected.\n";
		write_gro((char *)"out.gro", pos, n_beads, box);
	}

	free(pos);
	*/

	int choice[] = {-1, 0, 1};
	cout<<choice[(int)round(prng(2))]<<endl;

	return 0;
}