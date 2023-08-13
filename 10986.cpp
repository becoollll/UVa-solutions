#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define inf 1000000000
#define ii pair<int, int>

int latency[20010];
int n, m, s, t;
vector< vector<ii> > adj;

void Dijkstra(int s){
    //latency: 紀錄起點到每一點的最短距離
    for(int i = 0; i < n; i++){
        latency[i] = inf;
    }
    latency[s] = 0; //起點
    priority_queue<ii, vector<ii>, greater<ii> > pq; //greater: 由小到大
    pq.push( ii(latency[s], s) );
    ii p;
    int t, u;
    while(!pq.empty()){
        p = pq.top();
        pq.pop();
        t = p.first; //最短距離
        u = p.second; //頂點編號
        if(t > latency[u]){
            continue;
        }
        for(int i = 0; i < adj[u].size(); i++){
            if(latency[adj[u][i].first] > latency[u] + adj[u][i].second){
                latency[adj[u][i].first] = latency[u] + adj[u][i].second;
                pq.push( ii(latency[adj[u][i].first], adj[u][i].first) );
            }
        }
    }
}

int main(){
    int cases;
    cin >> cases;
    for(int k = 1; k <= cases; k++){
        cin >> n >> m >> s >> t;
        //n台伺服器, m條網路, 從伺服器 s 向伺服器 t 寄email所需的最短時間是多少
        adj.assign(n, vector<ii>(0));
        int x, y, l;
        for(int i = 0; i < m; i++){
            cin >> x >> y >> l;
            //伺服器x, y可以互相寄email, 時間為l
            adj[x].push_back( ii(y, l) );
            adj[y].push_back( ii(x, l) );
        }
        Dijkstra(s);
        cout << "Case #" << k << ": ";
        if(latency[t] != inf){
            cout << latency[t] << endl;
        }
        else{
            cout << "unreachable" << endl;
        }
    }
}