#pragma once
#include <vector>
using namespace std;
#define AX 0
#define AY 1
#define AZ 2
#define DEEPESTLEVEL 20
#define MINNODES 2
#define ISLEAF 0
#define NOTLEAF 1
#define EMPTY 2
class Box
{
public:
	double bmin[3];
	double bmax[3];
};
class Kdnode {
public:
	Kdnode();
	~Kdnode();
	bool isLeaf();
	bool isLeaf(Kdnode* N);
	bool isEmpty(Kdnode* N);
	void addRope(Kdnode* N);
	Kdnode* addLeftNode(Kdnode* N);
	Kdnode* addRightNode(Kdnode* N);
	void create();
public:
	std::vector<int> triangles;
	Kdnode *left;
	Kdnode *right;
	Box box;
	int AXIS;
	double splitPlane;
	int parentAXIS;
	double parent_splitPlane;
	int node_type;
	Kdnode* rope[6];
	int current_level;
	static int* tri;
	static double* x;
	static double* y;
	static double* z;
};
double* Kdnode::x = NULL;
double* Kdnode::y = NULL;
double* Kdnode::z = NULL;
int* Kdnode::tri = NULL;

Kdnode::Kdnode() {
	left = NULL;
	right = NULL;
	for (int nr = 0; nr < 6; nr++) {
		rope[nr] = NULL;
	}
	current_level = 0; // 0 is root node
	parentAXIS = -1;
	parent_splitPlane = 0.0;
	node_type = ISLEAF;
}
Kdnode::~Kdnode() {
	// TODO: implement the destructor
}
inline bool Kdnode::isLeaf() {
	if ( NULL == left && NULL == right && triangles.size() ) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Kdnode::isLeaf(Kdnode* N) {
	if (NULL == N->left && NULL == N->right && N->triangles.size()) {
		return true;
	}
	else {
		return false;
	}
}
inline bool Kdnode::isEmpty(Kdnode* N) {
	if (NULL == N->left && NULL == N->right && N->triangles.size()) {
		return true;
	}
	else {
		return false;
	}
}
inline void Kdnode::addRope(Kdnode * N)
{
	if (isLeaf(N)) {
		return;
	}
	else {
		for (int nr = 0; nr < 6; nr++) {
			N->left->rope[nr] = N->rope[nr];
			N->right->rope[nr] = N->rope[nr];
		}
		switch (N->AXIS) {
		case AX:
			N->left->rope[1] = N->right;
			N->left->rope[0] = N->left;
			break;
		case AY:
			N->left->rope[3] = N->right;
			N->left->rope[2] = N->left;
			break;
		case AZ:
			N->left->rope[5] = N->right;
			N->left->rope[4] = N->left;
			break;
		default:
			;
		}
	}
}
inline Kdnode* Kdnode::addLeftNode(Kdnode* N) {
	N->left = new Kdnode();
	return N->left;
}
inline Kdnode* Kdnode::addRightNode(Kdnode* N) {
	N->right = new Kdnode();
	return N->right;
}
void Kdnode::create() {
	cout << current_level << endl;
	if (DEEPESTLEVEL == current_level || triangles.size() < MINNODES) { // 达到规定深度直接返回
		return;
	}

	int tri_num = triangles.size(); // tri_num = Ntri

	double xmin = x[tri[triangles[0]]];
	double xmax = x[tri[triangles[0]]];
	double ymin = y[tri[triangles[0]]];
	double ymax = y[tri[triangles[0]]];
	double zmin = z[tri[triangles[0]]];
	double zmax = z[tri[triangles[0]]];
	for (int nloop = 0; nloop < tri_num; nloop++) {
		for (int nVer = 0; nVer < 3; nVer++) {
			if (x[tri[3 * triangles[nloop] + nVer]] < xmin) {
				xmin = x[tri[3 * triangles[nloop] + nVer]];
			}
			if (y[tri[3 * triangles[nloop] + nVer]] < ymin) {
				ymin = y[tri[3 * triangles[nloop] + nVer]];
			}
			if (z[tri[3 * triangles[nloop] + nVer]] < zmin) {
				zmin = z[tri[3 * triangles[nloop] + nVer]];
			}
			if (x[tri[3 * triangles[nloop] + nVer]] > xmax) {
				xmax = x[tri[3 * triangles[nloop] + nVer]];
			}
			if (y[tri[3 * triangles[nloop] + nVer]] > ymax) {
				ymax = y[tri[3 * triangles[nloop] + nVer]];
			}
			if (z[tri[3 * triangles[nloop] + nVer]] > zmax) {
				zmax = z[tri[3 * triangles[nloop] + nVer]];
			}
		}
	}
	//for (int k = 0; k < tri_num; k++) {
	//	if (xmin > x[tri[triangles[k]]]) {
	//		xmin = x[tri[k]];
	//		//cout << xmin << ',' << k << endl;
	//	}
	//	if (ymin > y[tri[k]]) {
	//		ymin = y[tri[k]];
	//	}
	//	if (zmin > z[tri[k]]) {
	//		zmin = z[tri[k]];
	//	}
	//	if (xmax < x[tri[k]]) {
	//		xmax = x[tri[k]];
	//	}
	//	if (ymax < y[tri[k]]) {
	//		ymax = y[tri[k]];
	//	}
	//	if (zmax < z[tri[k]]) {
	//		zmax = z[tri[k]];
	//	}
	//}
	box.bmin[0] = xmin;
	box.bmin[1] = ymin;
	box.bmin[2] = zmin;
	box.bmax[0] = xmax;
	box.bmax[1] = ymax;
	box.bmax[2] = zmax;
	double pos_x = 0.5 * (box.bmax[0] + box.bmin[0]);
	double pos_y = 0.5 * (box.bmax[1] + box.bmin[1]);
	double pos_z = 0.5 * (box.bmax[2] + box.bmin[2]);

	//vector<int> vx_left(tri_num);
	//vector<int> vy_left(tri_num);
	//vector<int> vz_left(tri_num);
	//vector<int> vx_right(tri_num);
	//vector<int> vy_right(tri_num);
	//vector<int> vz_right(tri_num);
	vector<int> vx_left(0);
	vector<int> vy_left(0);
	vector<int> vz_left(0);
	vector<int> vx_right(0);
	vector<int> vy_right(0);
	vector<int> vz_right(0);
	
	for (int nloop = 0; nloop < tri_num; nloop++) {
		//for (int nVer = 0; nVer < 3; nVer++) {
		int ind1 = tri[3 * triangles[nloop]];
		int ind2 = tri[3 * triangles[nloop] + 1];
		int ind3 = tri[3 * triangles[nloop] + 2];
		if (x[ind1] < pos_x || x[ind2] < pos_x || x[ind3] < pos_x) {
			vx_left.push_back(triangles[nloop]);
		}
		if (x[ind1] > pos_x || x[ind2] > pos_x || x[ind3] > pos_x) {
			vx_right.push_back(triangles[nloop]);
		}
		if (y[ind1] < pos_y || y[ind2] < pos_y || y[ind3] < pos_y) {
			vy_left.push_back(triangles[nloop]);
		}
		if (y[ind1] > pos_y || y[ind2] > pos_y || y[ind3] > pos_y) {
			vy_right.push_back(triangles[nloop]);
		}
		if (z[ind1] < pos_z || z[ind2] < pos_z || z[ind3] < pos_z) {
			vz_left.push_back(triangles[nloop]);
		}
		if (z[ind1] > pos_z || z[ind2] > pos_z || z[ind3] > pos_z) {
			vz_right.push_back(triangles[nloop]);
		}

		//}
	}
	if (abs((int)(vx_right.size() - vx_left.size())) > abs((int)(vy_right.size() - vy_left.size()))) {
		if (abs((int)(vz_right.size() - vz_left.size())) > abs((int)(vy_right.size() - vy_left.size()))) {
			AXIS = 1; // y axis
			splitPlane = pos_y;
			if (vy_left.size() && !(AXIS == parentAXIS && splitPlane==parent_splitPlane)) { // 左半盒非空，创建左子节点，新的条件：分割平面必须和之前的不同
				node_type = NOTLEAF;
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->triangles.swap(vy_left);
				left->parentAXIS = AXIS;
				left->parent_splitPlane = splitPlane;
				left->create();
			}
			else { //创建空节点
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->node_type = EMPTY;
			}
			if (vy_right.size() && !(AXIS == parentAXIS && splitPlane == parent_splitPlane)) { // 右半盒非空，创建右子节点
				node_type = NOTLEAF;
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->triangles.swap(vy_right);
				right->parentAXIS = AXIS;
				right->parent_splitPlane = splitPlane;
				right->create();
			}
			else { //创建空节点
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->node_type = EMPTY;
			}
		}
		else {
			AXIS = 2; // z axis
			splitPlane = pos_z;
			if (vz_left.size() && !(AXIS == parentAXIS && splitPlane == parent_splitPlane)) { // 左半盒非空，创建左子节点
				node_type = NOTLEAF;
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->triangles.swap(vz_left);
				left->parentAXIS = AXIS;
				left->parent_splitPlane = splitPlane;
				left->create();
			}
			else { //创建空节点
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->node_type = EMPTY;
			}
			if (vz_right.size() && !(AXIS == parentAXIS && splitPlane == parent_splitPlane)) { // 右半盒非空，创建右子节点
				node_type = NOTLEAF;
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->triangles.swap(vz_right);
				right->parentAXIS = AXIS;
				right->parent_splitPlane = splitPlane;
				right->create();
			}
			else { //创建空节点
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->node_type = EMPTY;
			}
		}
	}
	else {
		if (abs((int)(vz_right.size() - vz_left.size())) > abs((int)(vx_right.size() - vx_left.size()))) {
			AXIS = 0; // x axis
			splitPlane = pos_x;
			if (vx_left.size() && !(AXIS == parentAXIS && splitPlane == parent_splitPlane)) { // 左半盒非空，创建左子节点
				node_type = NOTLEAF;
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->triangles.swap(vx_left);
				left->parentAXIS = AXIS;
				left->parent_splitPlane = splitPlane;
				left->create();
			}
			else { //创建空节点
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->node_type = EMPTY;
			}
			if (vx_right.size() && !(AXIS == parentAXIS && splitPlane == parent_splitPlane)) { // 右半盒非空，创建右子节点
				node_type = NOTLEAF;
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->triangles.swap(vx_right);
				right->parentAXIS = AXIS;
				right->parent_splitPlane = splitPlane;
				right->create();
			}
			else { //创建空节点
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->node_type = EMPTY;
			}
		}
		else {
			AXIS = 2; // z axis
			splitPlane = pos_z;
			if (vz_left.size() && !(AXIS == parentAXIS && splitPlane == parent_splitPlane)) { // 左半盒非空，创建左子节点
				node_type = NOTLEAF;
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->triangles.swap(vz_left);
				left->parentAXIS = AXIS;
				left->parent_splitPlane = splitPlane;
				left->create();
			}
			else { //创建空节点
				left = new Kdnode;
				left->current_level = current_level + 1;
				left->node_type = EMPTY;
			}
			if (vz_right.size() && !(AXIS == parentAXIS && splitPlane == parent_splitPlane)) { // 右半盒非空，创建右子节点
				node_type = NOTLEAF;
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->triangles.swap(vz_right);
				right->parentAXIS = AXIS;
				right->parent_splitPlane = splitPlane;
				right->create();
			}
			else { //创建空节点
				right = new Kdnode;
				right->current_level = current_level + 1;
				right->node_type = EMPTY;
			}
		}
	}

	{
		//释放非叶节点的triangles向量
		if (node_type == NOTLEAF) {
			triangles.clear();
			vector<int>().swap(triangles);
		}
	}


	{
		//vx_left.clear();
		////vector<int>().swap(vx_left);
		//vx_right.clear();
		////vector<int>().swap(vx_right);
		//vy_left.clear();
		////vector<int>().swap(vy_left);
		//vy_right.clear();
		////vector<int>().swap(vy_right);
		//vz_left.clear();
		////vector<int>().swap(vz_left);
		//vz_right.clear();
		////vector<int>().swap(vz_right);
	}
	

	// 加入新的子节点

	//return this;
}