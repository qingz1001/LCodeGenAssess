#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 1001

int N, M;
int a[MAX_N];
int dp[MAX_N];
int prev[MAX_N];

void find_sequence(int L) {
    int i, j, max_len = 0, end = -1;
    
    memset(dp, 0, sizeof(dp));
    memset(prev, -1, sizeof(prev));
    
    for (i = 0; i < N; i++) {
        dp[i] = 1;
        for (j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            end = i;
        }
    }
    
    if (max_len < L) {
        printf("Impossible\n");
        return;
    }
    
    int sequence[MAX_N], seq_len = 0;
    while (end != -1 && seq_len < L) {
        sequence[seq_len++] = a[end];
        end = prev[end];
    }
    
    for (i = seq_len - 1; i >= 0; i--) {
        printf("%d ", sequence[i]);
    }
    printf("\n");
}

int main() {
    int i, L;
    
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    
    scanf("%d", &M);
    for (i = 0; i < M; i++) {
        scanf("%d", &L);
        find_sequence(L);
    }
    
    return 0;
}