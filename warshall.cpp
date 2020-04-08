#include <bits/stdc++.h>
using namespace std;
const int NMAX = 3000; // 配列もNMAXの値で初期化する必要有
const long long INF = 1e18+7;
//vectorは隣接行列で表記

vector<vector<long long>> Warshall(int n,vector<vector<long long>> graph){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                //負対応
                if(graph[i][k] == INF || graph[k][j] == INF) continue;
                graph[i][j] = min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }
    return graph;
}