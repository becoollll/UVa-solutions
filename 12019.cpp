#include <iostream>
using namespace std;
                    
int main(){
    int c;
    int month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    string week[7] = {"Friday","Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday"};
    cin >> c;
    while(c--){
        string ans = "";
        int a = 0, mon, day;
        cin >> mon >> day;
        if(mon!=1){
            for(int i = 0; i < mon-1; i++){
                a += month[i];
            }
        }
        a+=day;
        a%=7;
        cout << week[a] << endl;
    }
    return 0;
}