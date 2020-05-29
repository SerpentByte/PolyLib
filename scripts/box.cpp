#include <iostream>
#include <cstring>
#include "../headers/gromos87_io.h"
#include "../headers/box.h"
#include "../headers/xyz.h"

void usage()
{
	printf("Essential flags\n");
	printf("---------------------------\n");
	printf("box -flags <value>\n");
	printf("-beads\t<number of beads in the polymer\n");
	printf("-sig\t<size of one bead\n");
	printf("-box\t<a> <b> <c> (a, b, c are box side lengths)\n");
	printf("Optional flags\n");
	printf("---------------------------\n");
	printf("-bond <value>        Manual bond distance [default = sigma]\n");
	printf("-c                   Center polymer inside box (overrides -centre)\n");
	printf("-centre <x> <y> <z>  Define center [default (0,0,0)]\n");
	printf("-avoid <true/false>  Self avoiding beads [default true]\n");
	printf("-nt                  <number of CPU threads to use> [default = 1]\n");
	printf("-v                   Verbose. Print parameters.\n");
}

int main(int argc, char* args[])
{
	xyz *pos, box;

	box = xyz(10, 10, 10);
	int n_beads = 928, nt=1;
	double sig = 1, bond=-1;
	xyz centre = xyz();
	bool avoid = true,  cen_val=false, verbose=false;
	string opt_flag = "";
	int reqd=0;
	char *out = (char *)"out.gro";

	/*-----------------------------------
	|			Argument parser			|
	-----------------------------------*/

	if(argc<9)
	{
		cout<<"Incorrect usage.\n";
		usage();
		return 0;
	}

	for(int i=1;i<argc;i++)
	{
		opt_flag = args[i];

		//----------------------------------------essentials
		if(!opt_flag.compare("-beads"))
		{
			n_beads = atoi(args[i+1]);
			if(n_beads==0)
			{
				cout<<"Incorrect value of -beads.\n";
				return 0;
			}
			reqd++;
		}
		else if(!opt_flag.compare("-sig"))
		{
			sig = atof(args[i+1]);
			if(sig==0)
			{
				cout<<"Incorrect value of -sig.\n";
				return 0;
			}
			reqd++;
		}
		else if(!opt_flag.compare("-box"))
		{
			reqd++;
			box = xyz(atof(args[i+1]),
				atof(args[i+2]),atof(args[i+3]));
			if(box.x==0 || box.y==0 || box.z==0)
			{
				cout<<"Incorrect box dimensions.\n";
				return 0;
			}
		}
		//----------------------------------------optionals
		else if(!opt_flag.compare("-nt"))
		{
			if(i+1>=argc)
			{
				cout<<"Bad usage.\n"; usage();
				return 0;
			}
			nt = atoi(args[i+1]);
		}
		else if(!opt_flag.compare("-avoid"))
		{
			if(i+1>=argc)
			{
				cout<<"Bad usage.\n"; usage();
				return 0;
			}
			opt_flag = toLower(args[i+1]);
			if(!opt_flag.compare("false"))
				avoid = false;
		}
		else if(!opt_flag.compare("-centre"))
		{
			if(i+1>=argc || i+2>=argc || i+3>=argc)
			{
				cout<<"Bad usage.\n"; usage();
				return 0;
			}
			centre = xyz(atof(args[i+1]),
				atof(args[i+2]),atof(args[i+3]));
			if(centre.x*centre.y*centre.z==0)
			{
				cout<<"Bad usage.\n"; usage();
				return 0;
			}
		}
		else if(!opt_flag.compare("-c"))
			cen_val=true;
		else if(!opt_flag.compare("-v"))
			verbose = true;
		else if(!opt_flag.compare("-bond"))
		{
			if(i+1>=argc)
			{
				cout<<"Bad usage.\n"; usage();
				return 0;
			}
			bond = atof(args[i+1]);
			if(bond==0)
			{
				cout<<"Incorrect bond distance provided.\n";
				return 0;
			}
		}
		else if(!opt_flag.compare("-o"))
		{
			if(i+1 >= argc)
			{
				cout<<"ERROR: Bad usage in providing output name.\n";
				usage();
				return 0;
			}
			else if(args[i+1][0]=='-')
			{
				cout<<"ERROR: Bad usage in providing output name.\n";
				usage();
				return 0;
			}
			if(strlen(args[i+1])>20)
			{
				free(out);
				out = (char*)malloc(sizeof(char)*strlen(args[i+1]));
			}
			out = args[i+1];
		}
	}

	if(reqd<3)
	{
		cout<<"Incorrect usage.\n";
		usage();
		return 0;
	}
	if(cen_val)
	{
		centre = box/2;
	}

	if(verbose)
	{
		double temp = bond;
		bond = sig;
		printf("Beads=%d\nsigma=%.3lf\navoid=%d\nnt=%d\nbond=%.3lf\n", 
			n_beads, sig, avoid, nt, bond);
		cout<<"Centre="; centre.display();
		cout<<"Box="; box.display();
		cout<<"Output= "<<out<<endl;
		cout<<"---------------------------------------\n";
		bond = temp;
	}

	pos = boxed(n_beads, sig, box, centre, verbose);
		
	if(pos!=NULL)
		write_gro(out, pos, n_beads, box);

	free(pos);

	return 0;
}