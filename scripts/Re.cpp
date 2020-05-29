#include <iostream>
#include <cstring>
#include "../headers/Re.h"

void usage()
{
	printf("Usage:\n");
	printf("-f\t<.gro file name>\n");
}

int main(int argc, char* args[])
{
	double Re=0;
	int n_beads=10, reqd=0;
	double sig=1;
	char *name = (char *)"out.gro";
	string opt_flag="";
	/*-----------------------------------
	|			Argument parser			|
	-----------------------------------*/

	if(argc<3)
	{
		cout<<"Incorrect usage.\n";
		usage();
		return 0;
	}

	for(int i=1;i<argc;i++)
	{
		opt_flag = args[i];

		//----------------------------------------essentials
		if(!opt_flag.compare("-f"))
		{
			if(i+1 >= argc)
			{
				cout<<"ERROR: Bad usage in providing gro file name.\n";
				usage();
				return 0;
			}
			else if(args[i+1][0]=='-')
			{
				cout<<"ERROR: Bad usage in providing gro file name.\n";
				usage();
				return 0;
			}
			if(strlen(args[i+1])>20)
			{
				free(name);
				name = (char*)malloc(sizeof(char)*strlen(args[i+1]));
			}
			name = args[i+1];
			reqd++;
		}		
	}

	if(reqd<1)
	{
		cout<<"Incorrect usage.\n";
		usage();
		return 0;
	}

	Re = re(name);
		
	cout<<Re<<endl;

	return 0;
}