#include <stdio.h>

typedef long long ll;

int main(){
    int n;
    ll p;
    scanf("%d %lld", &n, &p);
    ll z[n], a[n], b[n];
    for(int i=0;i<n;i++) scanf("%lld %lld %lld", &z[i], &a[i], &b[i]);
    ll left=0, right=2e14, mid, total;
    while(left < right){
        mid = left + (right - left)/2;
        total = 0;
        for(int i=0;i<n;i++){
            if(mid <= z[i]){
                total += a[i] * mid;
            }
            else{
                total += a[i] * z[i] + b[i] * (mid - z[i]);
            }
            if(total >= p) break;
        }
        if(total >= p){
            right = mid;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld", left);
}