#include <stdio.h>
#include <math.h>

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    double L[N];
    double maxL = 0.0;
    for(int i=0;i<N;i++){
        scanf("%lf", &L[i]);
        if(L[i] > maxL) maxL = L[i];
    }
    double low = 0.0, high = maxL, mid;
    for(int i=0;i<100;i++){
        mid = (low + high) / 2.0;
        if(mid == 0.0){
            low = 0.0;
            break;
        }
        long long total = 0;
        for(int j=0;j<N;j++) {
            total += (long long)(L[j] / mid);
        }
        if(total >= K){
            low = mid;
        }
        else{
            high = mid;
        }
    }
    long long temp = (long long)(low * 100.0);
    double result = temp / 100.0;
    printf("%.2lf", result);
    return 0;
}