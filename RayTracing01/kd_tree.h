#pragma once
#include <vector>
#define AX 0
#define AY 1
#define AZ 2
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
public:
	std::vector<int> triangles;
	Kdnode *left;
	Kdnode *right;
	Box box;
	int AXIS;
	double splitPlane;
	Kdnode* rope[6];
};
Kdnode::Kdnode() {
	left = NULL;
	right = NULL;
	for (int nr = 0; nr < 6; nr++) {
		rope[nr] = NULL;
	}
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