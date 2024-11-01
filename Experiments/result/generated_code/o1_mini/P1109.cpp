#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    long long sum = 0;
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
        sum += a[i];
    }
    int L, R;
    scanf("%d %d", &L, &R);
    long long min_sum = (long long)n * L;
    long long max_sum = (long long)n * R;
    if(sum < min_sum || sum > max_sum){
        printf("-1\n");
        return 0;
    }
    long long excess = 0;
    for(int i=0;i<n;i++){
        if(a[i] > R){
            excess += a[i] - R;
        }
    }
    printf("%lld\n", excess);
    return 0;
}