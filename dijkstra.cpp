#include <bits/stdc++.h>
using namespace std;

/**
* An algorithm finds the cost of the shortest path between two nodes.
* O((N+M)logN)
* 
* @example Dijkstra hoge(graph,start,size); 
*          cout << hoge.get_cost(4) << endl;
*/
class Dijkstra{
    private:
        vector<vector<pair<int,long long>>> graph; //pair<next_path,cost>
        vector<long long> total_cost;
    
    public:
        /**
         * @brief Construct a new Dijkstra object
         * 
         * @param graph vector<vector<pair<int,ll>>>, pair.first is next node, pair.second is edge cost
         * @param start int
         * @param size int 
         * @param path_check bool
         */
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
        /**
         * @brief Get the cost object
         * 
         * @param goal long long
         * @return answer long long
         */
        long long get_cost(int goal){ return total_cost[goal]; }
};