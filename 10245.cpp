#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

class Point{
public:
    double x;
    double y;
};

Point P[10000];
Point tmp[10000];

int N;

double dist(const Point &l, const Point &r){
    return sqrt(pow(l.x - r.x, 2) + pow(l.y - r.y, 2));
}

bool X(const Point &l, const Point &r){
    return l.x < r.x;
}

bool Y(const Point &l, const Point &r){
    return l.y < r.y;
}

double solve(int L, int R)
{
    if (L >= R){
        return 1e9;
    }

    int M = (L + R) / 2;
    double d = min(solve(L, M), solve(M + 1, R)); // 左右兩邊最接近的

    int idx = 0;
    for (int i = M; i >= L && P[M].x - P[i].x < d; --i){ //離"中間垂直線"距離 < d的點存進tmp
        tmp[idx++] = P[i];
    }
    for (int i = M + 1; i <= R && P[i].x - P[M].x < d; ++i){
        tmp[idx++] = P[i];
    }

    sort(tmp, tmp + idx, Y); // 依照y座標排序 O(nlogn)


    for(int i = 0; i < idx; i++){
        for(int j = 1; j < 4 && i + j < idx; j++){
            d = min(dist(tmp[i], tmp[i + j]), d); // 找出tmp裡所有點的最短距離 還有d的距離 取最小值
        }
    }
    return d;
}

int main(){
    while (cin >> N && N){
        for(int i = 0; i < N; i++){
            cin >> P[i].x >> P[i].y;
        }
        sort(P, P + N, X); // 依照x座標排序

        double ans = solve(0, N - 1);
        if (ans >= 1e4){
            cout << "INFINITY"<< endl;
        }
        else{
            cout << fixed << setprecision(4) << ans << endl;
        }
    }
}