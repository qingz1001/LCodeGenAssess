#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

int main(){
    int N;
    scanf("%d", &N);
    double M[N+1];
    for(int i=1;i<=N;i++) scanf("%lf", &M[i]);
    double prefix[N+1];
    prefix[0]=0.0;
    for(int i=1;i<=N;i++) prefix[i]=prefix[i-1]+M[i];
    double total_sum = prefix[N];
    double left=0.0, right=10000.0, mid, eps=1e-7;
    for(int it=0; it<100; it++){
        mid=(left+right)/2.0;
        double target = total_sum - mid * N;
        double F[N+1];
        for(int i=0;i<=N;i++) F[i]=prefix[i]-mid*i;
        double min_F = F[1];
        int possible=0;
        for(int j=2;j<=N-1;j++){
            if(F[j] - min_F >= target){
                possible=1;
                break;
            }
            if(F[j-1] < min_F) min_F = F[j-1];
        }
        if(possible) {right=mid;}
        else {left=mid;}
    }
    double result = right;
    // Round to three decimal places
    result = floor(result * 1000.0 + 0.5) / 1000.0;
    printf("%.3lf\n", result);
}