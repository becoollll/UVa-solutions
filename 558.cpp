#include <iostream>
#define MAX 100000000
using namespace std;

int x[2001], y[2001], t[2001];

bool BellmanFord(int n, int m){
    int d[2001];
    fill(d, d + n, MAX);
    d[0] = 0; // 第0個點為起點
    // bellman ford
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < m; j++){
            if (d[x[j]] != MAX){
                if (d[x[j]] + t[j] < d[y[j]]){
                    d[y[j]] = d[x[j]] + t[j];
                }
            }
        }
    }
    // 有負環
    for (int j = 0; j < m; j++){
        if (d[x[j]] + t[j] < d[y[j]]){
            return true;
        }
    }
    return false;
}

int main(){
    int Case, n, m;
    cin >> Case;
    while (Case--){
        int i;
        cin >> n >> m;
        for (i = 0; i < m; i++){
            cin >> x[i] >> y[i] >> t[i];
            // 點 x[i] 連接到點 y[i] (單向) 且 weight 為 t[i]


        }
        if(BellmanFord(n, m)){
            cout << "possible" << endl;
        }
        else{
            cout << "not possible" << endl;
        }
    }
}