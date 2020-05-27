#include<bits/stdc++.h>
using namespace std;

vector<int> seq;

struct CartesianTree {
	int n;
	CartesianTree *left, *right;
	CartesianTree(int val, CartesianTree *l, CartesianTree *r): n(val), left(l), right(r) {}
};

CartesianTree* buildTree(int i, int j) {
	if(i > j)	return NULL;
	if(i == j)	return new CartesianTree(seq[i], NULL, NULL);
	int max_val = seq[i], index = i;
	for(int k = i+1; k <= j; ++k) {
		if(max_val < seq[k])	max_val = seq[k], index = k;
	}
	return new CartesianTree(seq[index], buildTree(i, index-1), buildTree(index+1, j));
}

void printTree(CartesianTree* root) {
	if(root == NULL) {
		cout << "(N)";
		return;
	}
	cout << '(';
	printTree(root->left);
	cout << root->n;
	printTree(root->right);
	cout << ')';
}

int main()
{
	int n;
	cout << "Enter size of the sequence: ";
	cin >> n;
	seq.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> seq[i];
	}
	CartesianTree *root = buildTree(0, n-1);

	printTree(root);
	cout << endl;
	return 0;
}