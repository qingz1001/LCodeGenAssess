#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int A, B, N;
    scanf("%d", &A);
    scanf("%d", &B);
    scanf("%d", &N);
    int initial[] = {0,990,1010,1970,2030,2940,3060,3930,4060,4970,5030,5990,6010,7000};
    int size = 14 + N;
    int motels[34];
    for(int i=0;i<14;i++) motels[i] = initial[i];
    for(int i=14;i<14+N;i++) scanf("%d", &motels[i]);
    qsort(motels, 14+N, sizeof(int), cmp);
    int unique[34];
    int m = 0;
    unique[m++] = motels[0];
    for(int i=1;i<14+N;i++) {
        if(motels[i] != motels[i-1]) unique[m++] = motels[i];
    }
    // Ensure 7000 is present
    if(unique[m-1] != 7000){
        unique[m++] = 7000;
    }
    ll dp[34];
    for(int i=0;i<m;i++) dp[i] = 0;
    dp[0] = 1;
    for(int i=1;i<m;i++){
        for(int j=i-1;j>=0;j--){
            int diff = unique[i] - unique[j];
            if(diff < A) break;
            if(diff > B) continue;
            dp[i] += dp[j];
        }
    }
    printf("%lld\n", dp[m-1]);
    return 0;
}