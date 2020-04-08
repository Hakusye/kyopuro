#include <bits/stdc++.h>
using namespace std;

class UnionFind{
	private:
		vector<int> Parent; //parent is -(size).

	public:
		UnionFind(int N){
			Parent = vector<int>(N,-1);
		}

		int find_parent(int A){ 
			if(Parent[A]<0) return A;
			return Parent[A] = find_parent(Parent[A]);
		}

		int size(int A){
			return -Parent[find_parent(A)];
		}

		bool connect(int A,int B){
			A = find_parent(A);
			B = find_parent(B);
			if(A == B) return false;
			if(size(A) < size(B)) swap(A,B);
			Parent[A] += Parent[B];
			Parent[B] = A;
			return true;
		}
};
