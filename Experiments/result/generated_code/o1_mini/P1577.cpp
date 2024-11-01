#include <stdio.h>
#include <math.h>

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    double L[N];
    double maxL = 0.0;
    for(int i=0;i<N;i++){
        scanf("%lf", &L[i]);
        if(L[i] > maxL){
            maxL = L[i];
        }
    }
    double low=0.0, high=maxL, mid, eps=1e-7;
    for(int i=0;i<100;i++){
        mid = (low + high) /2.0;
        if(mid < eps){
            low = mid;
            continue;
        }
        long long count=0;
        for(int j=0;j<N;j++){
            count += (long long)(L[j]/mid);
        }
        if(count >= K){
            low = mid;
        }
        else{
            high = mid;
        }
    }
    double x = floor(low * 100.0) / 100.0;
    printf("%.2lf", x);
    return 0;
}