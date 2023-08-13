#include <iostream>
#include <string.h>
using namespace std;

#define N 2005
#define M 10005

int dp[N][M], w[N], sum[N], pre[N][M], ans[N];

int main(){
    int cases;
    cin >> cases;
    while(cases--){
        int len;
        cin >> len; //港口長度
        len *= 100; //m to cm

        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        int n = 0;
        sum[0] = 0;
        int k;
        while(cin >> k, k != 0){ //k != 0
            n++; //start from 1
            w[n] = k; //第n輛車的長度
            sum[n] = sum[n-1] + k; //前i輛車的總長
        }
        int temp = -1;
        for(int i = 1; i <= n; i++){ //w[] start from 1 so i start from 1
            for(int j = 0; j <= len; j++){
                if(j >= w[i] && dp[i-1][j-w[i]]){ //放左邊
                    k = i; //最大能放的車輛數
                    temp = j; //左邊已經放的所有車的總長
                    dp[i][j] = 1; //左邊車佔了j長度時,可以放i輛車
                    pre[i][j] = j - w[i]; //前一次放的長度
                } 
                else if(sum[i]-j <= len && dp[i-1][j]){ //放右邊
                    k = i; 
                    temp = j;
                    dp[i][j] = 1;
                    pre[i][j] = j;
                }
            }
        }
        int num = k, j;
        while(num--){ //總車輛數
            j = pre[num+1][temp]; //+1是因為上面的雙for loop裡紀錄陣列的i是1開始，會多1
            if(j == temp){ //左邊
                ans[num] = 1;
            }
            else{ //右邊
                ans[num] = 0;
            }
            temp = j;
        }
        cout << k << endl;
        for(int i = 0; i < k; i++){
            if(ans[i] == 1){
                cout << "starboard" << endl;
            }
            else{
                cout << "port" << endl;
            }
        }
        if(cases){
            cout << endl;
        }
    }
    return 0;
}