#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;
const int maxn = 101;
const double inf = 100000000.000;
const double eps = 1e-6;

// 每個警察到每個銀行建立一條邊
class Edge {
public:
    int from, to, cap, flow; //capticity
    double cost; // 權重
    Edge(int u, int v, int c, int f, double w) : from(u), to(v), cap(c), flow(f), cost(w) {}
};

class MCMF{
public:
    int n, m;
    vector<Edge> edges;  // 整個圖
    vector<int> G[maxn]; // 存所有點、邊的關係
    int inq[maxn];       // 判斷一點有沒有在queue中(for SPFA)
    double d[maxn];      // 起點到d[i]的最短路徑
    int p[maxn];         // 紀錄路徑
    int a[maxn];         // 找到增廣路徑後

    void init(int n){
        this->n = n;
        for(int i = 0; i <= n; i++){
            G[i].clear();
        }
        edges.clear();
    }

    void AddEdge(int from, int to, int cap, double cost){
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost)); 
        m = edges.size();
        G[from].push_back(m - 2); // 按照邊的編號存
        G[to].push_back(m - 1);
    }

    bool BellmanFord(int s, int t, int &flow, double &cost){ // 找最短路徑
        for (int i = 0; i <= n; i++){
            d[i] = inf * 1.0;
        }
        memset(inq, 0, sizeof(inq));
        d[s] = 0;
        inq[s] = 1;
        p[s] = 0;
        a[s] = inf;

        queue<int> Q;
        Q.push(s);
        while (!Q.empty()){
            int u = Q.front();
            Q.pop();
            inq[u] = 0;
            for (int i = 0; i < G[u].size(); i++){
                Edge &e = edges[G[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost){ // 找可以走的邊(容量大於流量)
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if (!inq[e.to]){ // 判斷有沒有在queue裡
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if (d[t] >= inf){ // 如果d[t]沒有更新，等於沒有找到增廣路徑，沒有maximum flow, minimum cost
            return false;
        }
        flow += a[t]; // 更新maximum cost
        cost += (double)d[t] * (double)a[t]; //flow * 路徑長度
        for (int u = t; u != s; u = edges[p[u]].from){ //用p保存的上一個邊的值更新剛剛找到的增廣路徑的流量
            // 兩邊都要更新
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t]; 
        }
        return true;
    }

    int MincostMaxflow(int s, int t, double &cost){ //計算從s到t的minimum cost, return maximum flow
        int flow = 0;
        cost = 0;
        while (BellmanFord(s, t, flow, cost)); // 一直找增廣路徑直到找不到為止
        return flow;
    }
};

MCMF mcmf;

double tmp[21][21];
int main(){
    int n, m;
    //ios::sync_with_stdio(false);
    while (cin >> n >> m, n + m){
        mcmf.init(100);
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                cin >> tmp[i][j];
            }
        }
        mcmf.AddEdge(0, 1, n, 0);
        for (int i = 1; i <= m; i++){
            mcmf.AddEdge(1, i + 1, 1, 0);
        }
        for (int i = 1; i <= m; i++){
            for (int j = 1; j <= n; j++){
                mcmf.AddEdge(1 + i, 1 + m + j, 1, tmp[j][i]);
            }
        }
        for (int i = 1; i <= n; i++){
            mcmf.AddEdge(m + 1 + i, m + n + 2, 1, 0);
        }
        double ans;
        mcmf.MincostMaxflow(0, m + n + 2, ans);
        cout << fixed << setprecision(2) << (ans / n + eps) << endl;
    }
    return 0;
}