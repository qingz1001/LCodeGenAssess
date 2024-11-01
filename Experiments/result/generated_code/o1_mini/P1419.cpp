#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

int main(){
    int n, S, T;
    scanf("%d", &n);
    scanf("%d %d", &S, &T);
    double a[n];
    double min_a = 1e5, max_a = -1e5;
    for(int i=0;i<n;i++){
        scanf("%lf", &a[i]);
        if(a[i] < min_a) min_a = a[i];
        if(a[i] > max_a) max_a = a[i];
    }
    double low = min_a, high = max_a, mid, eps=1e-5;
    double prefix[n+1];
    while(high - low > eps){
        mid = (low + high) / 2.0;
        prefix[0] = 0.0;
        for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] + a[i-1] - mid;
        double min_prefix = 0.0;
        int valid = 0;
        for(int i=S;i<=n;i++){
            if(i-T-1 >=0){
                if(prefix[i-T-1] < min_prefix) min_prefix = prefix[i-T-1];
            }
            if(prefix[i-S] < min_prefix) min_prefix = prefix[i-S];
            if(prefix[i] - min_prefix >=0){
                valid = 1;
                break;
            }
        }
        if(valid){
            low = mid;
        }
        else{
            high = mid;
        }
    }
    printf("%.3lf\n", low);
}