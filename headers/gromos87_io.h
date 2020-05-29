#include <iostream>
#include <cstdio>
#include "xyz.h"

using namespace std;

#ifndef GRO_IO
#define GRO_IO
#define len 100

/*---------------------------------------------
Function to read cooridnates from GROMOS-87 format files
---------------------------------------------*/
xyz *read_gro(char *name)
{
	char temp[len];
	int n, cols, at_no;
	xyz v, box, *pos;

	//---------- check if velocities exist or not
	system("sed -n 3p pol_1.gro | wc -w > cols.txt");
	fscanf(fopen("cols.txt","r"),"%d", &cols);
	system("rm -rf cols.txt");
	//---------- check if velocities exist or not

	FILE *gro = fopen(name, "r");
	if(gro==NULL)
	{
		printf("%s not found.\n", name);
		return 0;
	}
	
	fgets(temp, len, gro); // reading heading

	fscanf(gro, "%d", &n); // reading the number of atoms

	pos = (xyz *)malloc(sizeof(xyz)*n);

	if(cols>9)
	{
		cout<<"Not a GROMOS-87 format file.";
		return 0;
	}

	for(int i=0;i<n;i++)
	{
		if(cols<=6)
			fscanf(gro,"%s %s %d %lf %lf %lf", 
				&temp, &temp, &at_no,
				&pos[i].x, &pos[i].y,  &pos[i].z);
		else if(cols>6)
			fscanf(gro,"%s %s %d %lf %lf %lf", 
				&temp, &temp, &at_no,
				&pos[i].x, &pos[i].y,  &pos[i].z,
				&v.x, &v.y,  &v.z);
	}

	fscanf(gro,"%lf %lf %lf", &box.x, &box.y, &box.z);

	printf("Number of monomers = %d\n",n);
	printf("Box dimensions = (%.3lf, %.3lf, %.3lf)\n", 
		box.x, box.y, box.z);

	fclose(gro);

	return pos;
}


/*---------------------------------------------
Function to write to a GROMOS-87 format files
---------------------------------------------*/
bool write_gro(char name[], xyz *pos, int n, xyz box, 
	char mol[]=(char*)"POL", char *atom=(char *)"H", 
	char head[]=(char *)"Generated using Polylib.")
{
	FILE *out = fopen(name, "w");

	fprintf(out, "%s\n", head);
	fprintf(out, "%d\n", n);

	for(int i=0;i<n;i++)
	{
		fprintf(out, "%5d%-5s%5s%5d%8.3lf%8.3lf%8.3lf\n",
			1, mol, atom, (i+1),
			pos[i].x, pos[i].y, pos[i].z);
	}

	fprintf(out, "   %.5lf %.5lf %.5lf\n", box.x, box.y, box.z);

	fclose(out);

	return true;
}
#endif
