#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a,long long b){
	while(1){
		if(a<b) swap(a,b);
		if(!b) break;
		a %= b;
	}
	return a;
}

inline long long lcm(long long a,long long b){return a*b/gcd(a,b);}
