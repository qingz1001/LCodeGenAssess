#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 1001

int N, M;
int S[MAX_N];
int dp[MAX_N];
int prev[MAX_N];

void find_sequence(int L) {
    int i, j, max_len = 0, last = -1;
    
    memset(dp, 0, sizeof(dp));
    memset(prev, -1, sizeof(prev));
    
    for (i = 0; i < N; i++) {
        dp[i] = 1;
        for (j = 0; j < i; j++) {
            if (S[j] < S[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            last = i;
        }
    }
    
    if (max_len < L) {
        printf("Impossible\n");
        return;
    }
    
    int result[MAX_N], count = 0;
    while (last != -1 && count < L) {
        result[count++] = S[last];
        last = prev[last];
    }
    
    for (i = L - 1; i >= 0; i--) {
        printf("%d", result[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}

int main() {
    int i, L;
    
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    
    scanf("%d", &M);
    for (i = 0; i < M; i++) {
        scanf("%d", &L);
        find_sequence(L);
    }
    
    return 0;
}