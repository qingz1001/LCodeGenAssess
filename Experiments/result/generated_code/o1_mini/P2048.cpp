#include <stdio.h>
#include <stdlib.h>

long long prefix_sum[100005];
long long *sums;
long long A[100005];
int cmp(const void *a, const void *b) {
    long long va = *(long long*)a;
    long long vb = *(long long*)b;
    if (va < vb) return 1;
    else if (va > vb) return -1;
    else return 0;
}

int main(){
    int n, k, L, R;
    scanf("%d %d %d %d", &n, &k, &L, &R);
    for(int i=1;i<=n;i++) {
        scanf("%lld", &A[i]);
        prefix_sum[i] = prefix_sum[i-1] + A[i];
    }
    // Maximum possible number of sums
    // To prevent memory issues, assume n <= 1000
    // Adjust size as needed
    long long max_sums = (long long)n * (R - L +1);
    sums = (long long*)malloc(sizeof(long long)*max_sums);
    long long cnt=0;
    for(int i=1;i<=n;i++){
        for(int len=L; len<=R; len++){
            if(i + len -1 > n) break;
            long long s = prefix_sum[i+len-1] - prefix_sum[i-1];
            sums[cnt++] = s;
        }
    }
    qsort(sums, cnt, sizeof(long long), cmp);
    long long res=0;
    for(int i=0;i<k && i < cnt;i++) res += sums[i];
    printf("%lld", res);
    free(sums);
    return 0;
}