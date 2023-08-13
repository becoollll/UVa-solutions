#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int num[100001];
int UP[100001];  // 有變大的數字的值
int upp[100001];  //每個數字up的表(index)
int DOWN[100001];
int downn[100001];
int up_Max, down_Max;

void up(int i){
    int temp = 0;
    while(num[i] > UP[temp] && temp < up_Max){
        temp++;
    }
    if(temp == up_Max) {
        UP[temp] = num[i];
        up_Max++;
    }
    else if(num[i] < UP[temp]){ // 數字變小時
        UP[temp] = num[i];
    }
    upp[i] = temp;
}

void down(int i){
    int temp = 0;
    while(num[i] > DOWN[temp] && temp < down_Max){
        temp++;
    }
    if(temp == down_Max){
        DOWN[down_Max] = num[i];
        down_Max++;
    }
    else if (num[i] < DOWN[temp]){ //數字變大時
        DOWN[temp] = num[i];
    }
    downn[i] = temp;
}
int main(){
    int N;
    while (scanf("%d", &N) != EOF) {
        up_Max = 0, down_Max = 0;
        for (int i = 0; i < N; i++){
            cin >> num[i];
        }
        for (int i = 0, j = N - 1; i < N; i++, j--){
            up(i);
            down(j);
        }

        int Max = 0;
        for (int i = 0; i < N; ++i){
            if(min(upp[i], downn[i]) > Max){ // upp & downn 存的是array index
                Max = min(upp[i], downn[i]);
            }
        }
        cout << 2 * Max + 1 << endl;
    }
}
/*
input
10
1 2 3 4 5 4 3 2 1 10
output
Max = 4
UP:    1 2 3 4 5 10 0 0 0 0 
DOWN:  1 2 3 4 5  0 0 0 0 0 
upp:   0 1 2 3 4  3 2 1 0 5 
downn: 0 1 2 3 4  3 2 1 0 0
*/