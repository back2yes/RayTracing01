#include <iostream>
#include <fstream>
#include "kd_tree.h"
#include <math.h>
using namespace std;
int main()
{
	const int Nnodes = 294;
	const int Ntri = 566;
	//Kdnode* proot = new Kdnode();
	double* x = new double[Nnodes]();
	double* y = new double[Nnodes]();
	double* z = new double[Nnodes]();
	int* tri = new int[Ntri * 3]();
	const char* fn_tri = "tri.dat";
	const char* fn_x = "x.dat";
	const char* fn_y = "y.dat";
	const char* fn_z = "z.dat";

	fstream fs;
	fs.open(fn_tri, ios::binary | ios::in);
	//cout << sizeof(int) * Ntri * 3 << endl;
	fs.read((char*)tri, sizeof(int) * Ntri * 3);
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

	// Constructing the kd tree
	Kdnode* proot = new Kdnode();

	//proot->triangles.swap(vector<int>(Ntri)); //为最大的AABB盒分配三角面元存储空间
	proot->triangles.clear();
	for (int nt = 0; nt < Ntri; nt++) {
		proot->triangles.push_back(nt);
	}
	//getchar();

	Kdnode::x = x;
	Kdnode::y = y;
	Kdnode::z = z;
	Kdnode::tri = tri;
	proot->create();

	getchar();

	return 0;
}