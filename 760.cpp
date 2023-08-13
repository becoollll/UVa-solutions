#include <iostream>
#include <bits/stdc++.h>
#define N 2000
using namespace std;
string strA="", strB="";
// 要進行 suffix array 的字串，這裡的字串第一個 index 為 1
int sa[N], rk[N*2], oldrk[N*2], id[N], cnt[N] ;
// sa[i] 表示此字串所有後綴排序後第 i 大的 index
// rk[i] 表示此字串所有後綴排序後，字串中 index 後綴的排名。
// id = 舊的 sa 排名 , cnt 在 radix sort 時幫助
int n, m, maxn, lenA, lenB, flag = 0;
// n 字串長度 , m 文字的最大長度



void build_sa(){ //build suffix array
    int i, m, p, w; 
    // 在這邊把常在迴圈使用的變數名稱拉出來宣告，以避免不斷宣告造成的效率浪費
    n = strA.length()-1 ; // 減去 string[0] 的空格
    m = max(n, 300); // ascii 上限是 255
    memset(cnt, 0, sizeof(cnt)); // reset cnt
    memset(rk, 0, sizeof(rk)); // reset rk

    // radix sort開始 O(nlogn)
    for(i = 1; i <= n; i++){
        ++cnt[rk[i] = (int)strA[i]];
    }
    // rk[i] = (int) strA[i] 每一個字元在字串中排名
    //++cnt[rk[i] = (int)strA[i]] radix sort 分類
    for(i = 1; i <= m; i++){
        cnt[i] += cnt[i-1] ; 
    }
    //將 cnt 遞增排序方便之後找出數值排在第幾位
    for(i = n; i >= 1; i--){
        sa[cnt[rk[i]]--] = i ;
    }
    // cnt[rk[i]] 先找出字元在字串中排名再透過 cnt 找出他應該排在第幾位
    // 隨後進行 cnt[rk[i]]--，方便下一個值得排序位置。
    // radix sort結束

    for(w = 1; w < n; w *= 2){ // 倍增思想開始 w為1,2,4,8... O(nlogn)
        memset(cnt,0,sizeof(cnt)); //第一次 radix sort 開始，排序關鍵為後者
        //下面藍圈圈
        for(i = 1; i <= n; i++){
            id[i] = sa[i];
        }
        // id 用來記錄現在排序的順序，配合這次的 radix sort 再進行更動
        for(i = 1; i <= n; i++){
            ++cnt[rk[id[i]+w]] ;
        }
        for(i = 1; i <= m; i++){
            cnt[i] += cnt[i-1] ;
        }
        for(i = n; i >= 1; i--){
            sa[cnt[rk[id[i]+w]]--] = id[i] ;
        }
        // radix sort 與一開始相同，只是多增加 w，因為排序關鍵為後者
        // 第一次 radix sort 結束

        // 第二次 radix sort 開始，排序關鍵為前者
        memset(cnt, 0, sizeof(cnt));
        for(i = 1; i <= n; i++) id[i] = sa[i] ;
        for(i = 1; i <= n; i++) ++cnt[rk[id[i]]] ;
        for(i = 1; i <= m; i++) cnt[i] += cnt[i-1] ;
        for(i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i] ;
        // 第二次 radix sort 結束

        // 根據 radix sort再排列一次 rank 
        memcpy(oldrk, rk, sizeof(rk)); //複製 rank 來幫助 rank 間的交換
        for(p = 0, i = 1; i <= n; i++){ // p 為 rank 的等級，i 則是資料
            if(oldrk[sa[i]] == oldrk[sa[i-1]] && 
                oldrk[sa[i] + w] == oldrk[sa[i-1] + w])
                //如果與前一個 rank 值是相同則理應現在應該也要相同
                //最好範例：倍增排序圖示說明第一次排序的 rank[4~7], index 從 1 開始，
                //紅框框
                rk[sa[i]] = p ; //rank 字典排序不變
            else
                rk[sa[i]] = ++p ; //rank 字典排序增加
        }
    }
}

void build_lcp(){
    int lcp[N] = {} ;
    int max_lcp = 0 ; // max_lcp 最大長度
    //k 為現在 i 名的後綴與前一名後綴長度算出的最長共同前綴
    for(int i = 1 , k = 0 ; i <= n ; i++){
        if(k){
            k-- ;
        } 
        // 由於下次是把字串 index 在往後一個 index，所以 lcp 最差的情況則會是 x-1, 因為其實要比較的字串只是刪除上一個後綴的第一個字元
        
        while(strA[i+k] == strA[sa[rk[i]-1]+k]){
            ++k ;
        }
        // 比較順序每個每個 index 都是獨立,所以陣列都可以分開進行討論
        // 比較字串的 index 開始的後綴與他的 sa 前一項(sa-1)找出 lcp
        // strA[i] = 字串的 index 開始的後綴
        // strA[sa[rk[i]-1]] = 字串的 index 開始的後綴的 sa 前一項
        // while 裡面的 +k 則是減少重複比較，在上一次的 lcp 已經找出長度為 x 的 lcp

        lcp[rk[i]] = k ;
    }
    for(int i = 1 ; i <= n ; i++){
        if((sa[i] < lenA && sa[i-1] < n+1 && sa[i-1] > lenA ) ||
            (sa[i] > lenA && sa[i-1] < n+1 && sa[i-1] < lenA))
            max_lcp = max(max_lcp , lcp[i]);
    }

    if(flag){
        cout << endl ;
    }
    flag = 1 ;

    map<string,int> mp ;
    if(max_lcp == 0){
        cout << "No common sequence." << endl; 
        return;
    }
    
    for(int i = 1 ; i <= n ; i++){
        if((sa[i] < lenA && sa[i-1] < n+1 && sa[i-1] > lenA ) || (sa[i] > lenA && sa[i-1] < n+1 && sa[i-1] < lenA)){
            if(lcp[i] == max_lcp){
                string temp = strA.substr(sa[i] , max_lcp);
                if(mp[temp]){
                    continue;
                }
                else{
                    mp[temp] = 1 ;
                }
                cout << temp << endl ;
            }
        }
    }
}

int main(){
    while(cin >> strA >> strB){
        lenA = strA.length()+1;
        lenB = strB.length();
        strA = ' ' + strA + '$' + strB + '#'; // +空格讓之後的排序可以從1開始
        build_sa();
        build_lcp();
    }
    return 0;
}