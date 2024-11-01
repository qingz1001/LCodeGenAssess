#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll *x = (ll*)malloc(n * sizeof(ll));
    ll *y = (ll*)malloc(n * sizeof(ll));
    ll *s = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld %lld %lld", &x[i], &y[i], &s[i]);
    
    double left=1e-8, right=1e14, mid, eps=1e-7;
    for(int it=0; it<100; it++){
        mid = (left + right) / 2.0;
        double a = 0.0;
        int ok=1;
        for(int i=0;i<n;i++){
            double arrival = (double)s[i] / mid + a;
            if(arrival < (double)x[i]) arrival = (double)x[i];
            if(arrival > (double)y[i]){
                ok=0;
                break;
            }
            a = arrival;
        }
        if(ok){
            right = mid;
        }
        else{
            left = mid;
        }
    }
    printf("%.2lf\n", right);
    free(x);
    free(y);
    free(s);
    return 0;
}