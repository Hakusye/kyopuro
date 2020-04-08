#include <bits/stdc++.h>
using namespace std;

class Combination{
	private:
		const static long long MOD = 1e9+7;
		const static long long MAX = 510000;
		vector<long long> fact;
		vector<long long> finv;
		vector<long long> inv;
	public:
		Combination() : fact(MAX),finv(MAX),inv(MAX){ //n,k <=10^7くらいまで
			fact[0] = fact[1] = 1;
			finv[0] = finv[1] = 1;
			inv[1] = 1;
			for(int i=2;i<MAX;i++){
				fact[i] = fact[i-1] * i % MOD;
				inv[i] = MOD - inv[MOD%i] * (MOD/i) % MOD;
				finv[i] = finv[i-1] * inv[i] % MOD;
			}
		}

		long long nCk(long long n,long long k){
			if(n<k) return 0;
			if(n<0 || k<0) return 0;
			return fact[n] * (finv[k] * finv[n-k] % MOD) % MOD;
		}

		vector<long long> com; //n固定で n<=10^9, k <= 10^7
		void nCbigk(long long n){
			com.push_back(1);
            com.push_back(n);
            for(long long i=2;i<200010;i++){
                com.push_back((com[i-1] * (n-(i-1)) % MOD) * inv[i] % MOD);
            }
		}
};
