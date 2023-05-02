#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> adj_mtrx;
vector<vector<int>> dp_table;
int N, M, pos_SC, s, t, B;

void dp_dijkstra(int s){
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push(make_pair(0, make_pair(s, 0)));
    dp_table[s][0] = 0; 
    
    int v, k, dist, u, d;
    while(!pq.empty())
    {
        dist = pq.top().first;
        v = pq.top().second.first;
        k = pq.top().second.second; 
        pq.pop();
        if(dp_table[v][k] < dist) continue;

        for(auto edge: adj_mtrx[v])
        {
            u = edge.first;
            d = edge.second;
            int new_dist = dist + d;
            if(new_dist < dp_table[u][k])
            {
                dp_table[u][k] = new_dist;
                pq.push({new_dist, {u, k}});
            }   
            if(k+1 <= pos_SC && dist < dp_table[u][k+1])
            {
                dp_table[u][k+1] = dist;
                pq.push({dist, {u, k+1}});
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> s >> t >> B;
    pos_SC = N; // max number of shortcuts

    adj_mtrx.assign(N+1, vector<pair<int,int>>());
    int u, v, d;
    for(int i=0; i<M; i++) {
        cin >> u >> v >> d;
        adj_mtrx[u].push_back({v, d});
    }

    dp_table.assign(N+1, vector<int>(pos_SC+1, INT_MAX)); //dp_table[i][k]: minimum distance from s to i using k shortcuts

    dp_dijkstra(s);
    
    int minSC;
    int ans = INT_MAX;
    for(int i=0 ; i<pos_SC; i++) {
        ans = min(ans, dp_table[t][i]);
        if(ans <= B ) { 
            minSC=i; 
            break;
        }
    }
    cout << minSC << '\n';
    return 0;
}