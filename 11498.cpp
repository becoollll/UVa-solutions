#include<iostream>
using namespace std;
                    
int main(){
    while(1){
        int k;
        cin >> k;
        if(k == 0){
            break;
        }
        int n, m;
        cin >> n >> m;
        while(k--){
            int x, y;
            cin >> x >> y;
            if(x == n || y == m){
                cout << "divisa" << endl;
            }
            if(x > n && y > m){
                cout << "NE" << endl;
            }
            if(x > n && y < m){
                cout << "SE" << endl;
            }
            if(x < n && y > m){
                cout << "NO" << endl;
            }
            if(x < n && y < m){
                cout << "SO" << endl;
            }
        }
    }
    return 0;
}