#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

bool ok(double area, int N, int F, double *data){
    int sum = 0 ;
    for (int i = 0 ; i < N; i++){
        sum += data[i] / area;
    }
    return sum >= F + 1;
}

int main(){
    int cases;
    cin >> cases;
    //double data[10000];
    while(cases--){
        int N, F;
        cin >> N >> F;
            double data[N];
        double sum = 0;
        for(int i = 0; i < N; i++){
            cin >> data[i];
            data[i] = data[i] * data[i] * M_PI; //體積
            sum += data[i]; //Pie體積總和
        }
        double left = 0, right = sum, mid = (left + right) / 2;
        while((right-left) > 1e-5){ //10^(-5)->output要控制在小數點後四位
            if(ok(mid, N, F, data)){ //sum >= F+1
                left = mid; //代表可以再切更大片的蛋糕(往右搜尋)
            }
            else{
                right = mid;
            }
            mid = (left + right) / 2;
        }
        cout << fixed << setprecision(4) << left << endl;
    }
    return 0;
}