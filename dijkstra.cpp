#include <bits/stdc++.h>
using namespace std;

class Dijkstra{ //O((N+M)logN)
    private:
        vector<vector<pair<int,long long>>> graph; //pair<next_path,cost>
        vector<long long> total_cost;
    
    public:
        Dijkstra(vector<vector<pair<int,long long>>> graph,int start,int size,bool path_check = false){
            priority_queue<
                pair<int,long long>,
                vector<pair<int,long long>>,
                greater<pair<int,long long>>> q;
            vector<long long> cost(size,1e18+7);
            cost[start] = 0;
            q.push(make_pair(start,0ll));
            while (!q.empty()){
                auto now = q.top();
                q.pop();
                int prev = now.first;
                if( cost[prev] < now.second) continue;
                for (auto next : graph[prev]){
                    if (cost[next.first] <= cost[now.first] + next.second) continue;
                    cost[next.first] = cost[now.first] + next.second;
                    q.push(next);
                }
            }
            total_cost = cost;
        }
        long long get_cost(int goal){ return total_cost[goal]; }
};