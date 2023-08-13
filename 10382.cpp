#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 2e5 + 10;

class node{
public:
    double left;
    double right;
};

bool cmp1(node a, node b){
    return a.right > b.right;
}

int main(){
    node a[maxn];
    int n;
    double l, w;
    while(cin >> n >> l >> w){
        int cnt = 0;
        for(int i = 0; i < n; i++){
            double pos, r; //位置&半徑
            cin >> pos >> r;
            if (r * 2 <= w){ //半徑不超過w
                continue;
            }
            double x; //看下面的圖, 畢氏定理 x^2 = r^2 - (w/2)^2
            x = sqrt((2*r*2*r) - w*w) / 2; //wrong: sqrt((r*r -(w/2)^2));
            a[cnt].left = (double)pos - x; 
            a[cnt].right = (double)pos + x;
            cnt++;
        }
        sort(a, a + cnt, cmp1); //根據右邊端點從大到小排列
        int count = 0;
        double left = 0.0, right = (double)l;
        while (left < right){ //區間覆蓋 left >= right即結束
            int i = 0;
            for (i = 0; i < cnt; i++){
                if (a[i].left <= left && a[i].right > left){ //看下面的圖
                    count++;
                    left = a[i].right; //更新: left爲r[i], 直到left > right
                    break;
                }
            }
            if (i == cnt){ // 所有的元素沒有一個點符合條件，所以不可能覆蓋掉整個區間
                break;
            }
        }
        if (left < right){ //沒辦法覆蓋整個區間
            cout << "-1" << endl;
        }
        else{
            cout << count << endl;
        }
    }
}