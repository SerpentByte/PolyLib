#include <iostream>
#include <cmath>
#include <cstring>
#include "xyz.h"
#include "functions.h"

using namespace std;

#ifndef RE
#define RE
double re(char *name)
{
	int n, cols, at_no, len=100;
	xyz v, box, *pos;
	char temp[len];
	string s = string(name);
	char *cmd;

	FILE *gro = fopen(name, "r");
	if(gro==NULL)
	{
		printf("%s not found.\n", name);
		return 0;
	}
//-------------------------------------------------------Reading file
	//---------- check if velocities exist or not
	s = "sed -n 3p "+s+" | wc -w > cols.txt";
	cmd = (char*)malloc(sizeof(char)*s.length());
	strcpy(cmd, s.c_str());
	system(cmd);
	fscanf(fopen("cols.txt","r"),"%d", &cols);
	system("rm -rf cols.txt");
	//---------- check if velocities exist or not

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
	fclose(gro);
//-------------------------------------------------------Reading file

	xyz d = pos[0]-pos[n-1];
	d.sqr();

	double Re = sqrt(d.sum());

	return Re;
}
#endif