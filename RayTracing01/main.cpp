#include <iostream>
#include <fstream>
#include "kd_tree.h"
using namespace std;
int main()
{
	const int Nnodes = 294;
	const int Ntri = 566 * 3;
	Kdnode* proot = new Kdnode();
	double* x = new double[Nnodes]();
	double* y = new double[Nnodes]();
	double* z = new double[Nnodes]();
	int* tri = new int[Ntri]();
	const char* fn_tri = "tri.dat";
	const char* fn_x = "x.dat";
	const char* fn_y = "y.dat";
	const char* fn_z = "z.dat";

	fstream fs;
	fs.open(fn_tri, ios::binary | ios::in);
	fs.read((char*)tri, sizeof(int) * Ntri);
	fs.close();
	fs.open(fn_x, ios::binary | ios::in);
	fs.read((char*)x, sizeof(double) * Nnodes);
	fs.close();
	fs.open(fn_y, ios::binary | ios::in);
	fs.read((char*)y, sizeof(double) * Nnodes);
	fs.close();
	fs.open(fn_z, ios::binary | ios::in);
	fs.read((char*)z, sizeof(double) * Nnodes);
	fs.close();




	fs << sizeof(double) << endl;
	fs.close();
	getchar();

	return 0;
}