#pragma once
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

//structure of node
struct Node {
	int key;
	bool color;
	Node *left, *right;
};

//create a node with a value
Node* CreateNode(int key) {
	Node* res = new Node;
	res->key = key;
	res->left = NULL;
	res->right = NULL;
	return res;
}

//pre-order traversal
void NLR(Node* root) {
	if (root) {
		cout << root->key << " ";
		NLR(root->left);
		NLR(root->right);
	}
}

//in-order traversal
void LNR(Node* root) {
	if (root) {
		LNR(root->left);
		cout << root->key << " ";
		LNR(root->right);
	}
}

//post-order traversal
void LRN(Node* root) {
	if (root) {
		LRN(root->left);
		LRN(root->right);
		cout << root->key << " ";
	}
}

//level-order traversal
void LevelOrder(Node* root) {
	queue <Node*> q;
	Node* item;
	q.push(root);
	while (!q.empty()) {
		item = q.front();
		cout << item->key << " ";
		if (item->left)
			q.push(item->left);
		if (item->right)
			q.push(item->right);
		q.pop();
	}
}

//binary search
Node* Search(Node* root, int x) {
	if (!root)  return NULL;
	if (root->key < x) return Search(root->right, x);
	if (root->key > x) return Search(root->left, x);
	return root;
}

//insert a value into a BST
void Insert(Node* &root, int x) {
	if (!root) root = CreateNode(x);
	if (root->key < x) Insert(root->right, x);
	if (root->key > x) Insert(root->left, x);
}

//delete a node from a BST
void del(Node* &r, Node* &q) {
	if (r->right) del(r->right, q);
	q->key = r->key;
	q = r;
	r = r->left;
}

void Remove(Node* &root, int x) {
	if (!root) return;
	if (root->key < x) Remove(root->right, x);
	else if (root->key > x) Remove(root->left, x);
	else {
		Node* q = root;
		if (!q->left) root = q->right;
		else if (!q->right) root = q->left;
		else del(root->left, q);
		delete q;
	}
}

//create a BST with an array
Node* CreateTree(int a[], int n) {
	Node* root = NULL;
	for (int i = 0; i < n; ++i)
		Insert(root, a[i]);
	return root;
}

//remove all nodes of BST
void RemoveTree(Node* &root) {
	if (!root) return;
	if (root->left)
		RemoveTree(root->left);
	if (root->right)
		RemoveTree(root->right);
	if (!root->left && !root->right)
		delete root;
}

//calculate height of BST
int Height(Node* root) {
	if (root) {
		return max(Height(root->right) + 1, Height(root->left) + 1);
	}
	return 0;
}

//count the number of nodes
int CountNode(Node* root) {
	if (root)
		return CountNode(root->left) + CountNode(root->right) + 1;
	else
		return 0;
}

//summary of all values
int SumNode(Node* root) {
	if (root)
		return SumNode(root->left) + SumNode(root->right) + root->key;
	else
		return 0;
}

//calculate the height of a node
int HeightNode(Node* root, int x) {
	Node* tmp = Search(root, x);
	return Height(tmp);
}

//show level of a node
int Level(Node* root, Node* p) {
	return Height(root) - Height(p);
}

//count the number of leaf nodes
int CountLeaf(Node* root) {
	if (!root) return 0;
	if (!root->left && !root->right)
		return 1;
	else
		return CountLeaf(root->left) + CountLeaf(root->right);
}

//count the number of nodes that are less than x
int CountLess(Node* root, int x) {
	if (!root) return 0;
	if (root->key < x)
		return 1 + CountLess(root->left, x) + CountLess(root->right, x);
	else
		return CountLess(root->left, x);
}

// count the number of nodes that are greater than x
int CountGreater(Node* root, int x) {
	if (!root) return 0;
	if (root->key > x)
		return 1 + CountLess(root->left, x) + CountLess(root->right, x);
	else
		return CountLess(root->right, x);
}

//check if it is a BST
void Check(Node* root, vector<int>&a) {
	if (root) {
		Check(root->left, a);
		a.push_back(root->key);
		Check(root->right, a);
	}
}

bool IsBST(Node* root) {
	vector<int>a;
	Check(root, a);
	for (int i = 0; i < a.size() - 1; ++i)
		if (a[i] >= a[i + 1])
			return false;
	return true;
}

//check if it is a full BST
bool IsFull(Node* root) {
	if (root) {
		if ((root->left && !root->right) || (!root->left && root->right))
			return false;
		return IsFull(root->left) && IsFull(root->right);
	}
	return true;
}

bool IsFullBST(Node* root) {
	return IsBST(root) && IsFull(root);
}

//insert a node into a BST
void InsertNode(Node* &root, Node* x) {
	if (!root) root = x;
	if (root->key < x->key) InsertNode(root->right, x);
	if (root->key > x->key) InsertNode(root->left, x);
}

//copy a BST to another BST
void BSTtoBST(Node* src, Node* &des) {
	if (!src) return;
	Node* L = src->left;
	Node* R = src->right;
	src->left = NULL; src->right = NULL;
	InsertNode(des, src);
	BSTtoBST(L, des);
	BSTtoBST(R, des);
}

//find the index of median element 
int Median(Node* root, int n, int tmp) {
	if (tmp + CountLess(root, root->key) == n / 2) return root->key;
	if (tmp + CountLess(root, root->key) < n / 2) return Median(root->right, n, tmp + CountLess(root, root->key) + 1);
	return Median(root->left, n, tmp);
}

int GetMedian(Node* root) {
	return Median(root, CountNode(root), 0);
}



