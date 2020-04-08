#include <bits/stdc++.h>
using namespace std;

template< typename T>
struct BinaryIndexedTree{
    vector<T> bit;
    BinaryIndexedTree(int size){
        bit.assign(size+1,0);
    }

    void add(int k, T num){
        k++;
        // k & -kで一番したのたってるbitを取り出せる
        for(k;k < bit.size();k += k & -k){
            bit[k] += num;
        }
    }
    T sum(int k) {
        T ret = 0;k++;
        for(k;k>0;k -= k & -k){
            ret += bit[k];
        }
        return ret;
    }
};

