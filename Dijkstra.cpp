#include <bits/stdc++.h>
using namespace std;

class Dijkstra{ //O((N+M)logN)
    private:
        vector<vector<pair<int,long long>>> graph; //pair<next.path,cost>
        vector<long long> total_cost;
        vector<vector<int>>  shortest_path;
    
    public:
        Dijkstra(vector<vector<pair<int,long long>>> graph,int start,int size,bool path_check = false){
            priority_queue<
                pair<int,long long>,
                vector<pair<int,long long>>,
                greater<pair<int,long long>>> q;
            vector<long long> cost(size,1e18+7);
            vector<vector<int>> path(size);
            if(path_check) for(int i=0;i<size;i++) path[i].push_back(i);//自分は必ず通る
            cost[start] = 0;
            q.push(make_pair(0ll,start));
            while (!q.empty()){
                auto now = q.top();
                q.pop();
                int prev = now.first;
                if( cost[prev] < now.second) continue;
                for (auto next : graph[prev]){
                    if (cost[next.first] <= cost[now.first] + next.second) continue;
                    cost[next.first] = cost[now.first] + next.second;
                    //先頭からpathを追加
                    if(path_check) path[next.first].insert(path[next.first].begin(),path[now.second].begin(),path[now.second].end()); 
                    q.push(next);
                }
            }
            total_cost = cost;
            if(path_check) shortest_path = path;
        }
        vector<long long> get_cost(){ return total_cost; }
        vector<vector<int>> get_path(){ return shortest_path; }
};