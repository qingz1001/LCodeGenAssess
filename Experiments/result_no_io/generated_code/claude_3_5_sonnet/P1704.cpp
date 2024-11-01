#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 500000

int N, K;
int p[MAX_N], c[MAX_N];
bool must[MAX_N + 1];
int dp[MAX_N + 1];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d", &N, &K);
    
    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]);
        must[p[i]] = true;
    }
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &c[i]);
    }
    
    qsort(p, K, sizeof(int), compare);
    
    int last = 0, max_days = 0;
    for (int i = 1; i <= N; i++) {
        if (must[i]) {
            if (c[i] <= last) {
                printf("impossible\n");
                return 0;
            }
            last = c[i];
            max_days++;
        } else {
            dp[i] = (c[i] > last) ? max_days + 1 : max_days;
        }
    }
    
    for (int i = N; i >= 1; i--) {
        if (!must[i] && c[i] > last) {
            max_days = dp[i];
            last = c[i];
        }
    }
    
    printf("%d\n", max_days);
    return 0;
}