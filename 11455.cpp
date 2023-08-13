#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int c;
    cin >> c;
    while(c--){
        int kk[4];
        for(int i = 0; i < 4; i++){
            cin >> kk[i];
        }
        sort(kk,kk+4);
        if(kk[0]==kk[3]){
            cout << "square" << endl;
        }
        else if(kk[0]==kk[1] && kk[2]==kk[3]){
            cout << "rectangle" << endl;
        }
        else if(kk[0]+kk[1]+kk[2] >= kk[3]){
            cout << "quadrangle" << endl;
        }
        else{
            cout << "banana" << endl;
        }
    }
}