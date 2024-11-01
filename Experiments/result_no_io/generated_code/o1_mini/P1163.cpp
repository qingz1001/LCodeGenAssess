#include <stdio.h>
#include <math.h>

typedef long long ll;

int main(){
    ll w0, w, m;
    scanf("%lld %lld %lld", &w0, &w, &m);
    double left = 0.0, right = 3.0, mid, res = 0.0;
    for(int i = 0; i < 100; i++){
        mid = (left + right) / 2.0;
        double rate = mid;
        double amount = w0;
        for(int j = 0; j < m; j++){
            amount = amount * (1.0 + rate) - w;
            if(amount < -1e-8) break;
        }
        if(amount > 0){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    res = mid * 100.0;
    res = floor(res * 10.0 + 0.5) / 10.0;
    printf("%.1lf%%\n", res);
    return 0;
}