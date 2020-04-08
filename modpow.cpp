#include <bits/stdc++.h>
using namespace std;
long long modpow(long long a,long long n,long long p = 1e9+7){
    long long result = 1;
    while(n > 0){
        if(n & 1) (result *= a) %= p;
        (a*=a) %= p;
        n >>= 1;
    }
    return result;
}