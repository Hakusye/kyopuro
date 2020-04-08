#include <bits/stdc++.h>
using namespace std;

class Eratosthenes{ //NMAX変更しておｋ
    private:
        const static int NMAX = 200010;
        vector<bool> prime;
    
    public:
        Eratosthenes(){
            prime.resize(NMAX,true);//一旦全部trueとする(true=素数)
            prime[0] = false;
            prime[1] = false;
            for(int i=2;i*i<=NMAX;i++){
                if(prime[i]){
                    for(int j=2;i*j<=NMAX;j++) prime[i*j] = false;
                }
            }
        }
        inline vector<bool> isPrime(){ return prime; }

};