#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;

long long modPow(long long a, long long b) {
	if(b == 0)	return 1;
	if(b == 1)	return a;
	long long x = modPow((a*a) % MOD, b/2);
	if(b&1)	x = (x*a) % MOD;
	return x;
}

vector<long long> fact;

long long noOfWays(long long n) {
	if(n <= 1)	return 1;
	long long pow = 1, c = 0;
	while(c + pow <= n) {
		c += pow;
		pow <<= 1;
	}
	long long left, right, ways;
	// elements in the right subtree
	right = c/2;
	if(c + pow/2 < n) {
		right += n - (c + pow/2);
	}
	// elements in the left subtree
	left = n - 1 - right;
	// total ways to divide the elements in left and right subtree i.e, (n-1)C(left)
	ways = ((fact[n-1] * modPow(fact[left], MOD-2)) % MOD * modPow(fact[right], MOD-2)) % MOD;
	return ((ways * noOfWays(left)) % MOD * noOfWays(right)) % MOD;
}

int main()
{
	int n;
	cout << "Enter N:\n";
	cin >> n;
	int a[n];
	fact.resize(n+1);
	fact[0] = 1;
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		fact[i+1] = (fact[i] * (i+1)) % MOD;
	}
	/*
	* assuming "a" has distinct numbers, the solution will be independent of the numbers
	* since the solution can be large, we will compute solution % MOD
	*/
	cout << noOfWays(n) << endl;
	return 0;
}