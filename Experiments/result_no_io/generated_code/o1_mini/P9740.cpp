#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a[n], b[n];
    long long total = 0;
    for(int i=0;i<n;i++){
        scanf("%d %d", &a[i], &b[i]);
        total += (long long)b[i] * (100 / a[i]);
    }
    long long t;
    scanf("%lld", &t);
    if(total >= t){
        printf("Already Au.\n");
        return 0;
    }
    for(int i=0;i<n;i++){
        int remaining = a[i] - b[i];
        int score_per = 100 / a[i];
        long long needed = t - total;
        // Calculate c_j = ceil(needed / score_per)
        long long c_j = (needed + score_per -1) / score_per;
        if(c_j <= remaining && c_j >0){
            printf("%lld\n", c_j);
        }
        else{
            printf("NaN\n");
        }
    }
    return 0;
}