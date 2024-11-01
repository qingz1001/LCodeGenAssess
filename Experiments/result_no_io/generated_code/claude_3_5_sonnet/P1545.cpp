#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_L 1000001
#define MAX_N 1001

int N, L, A, B;
int S[MAX_N], E[MAX_N];
int dp[MAX_L];
int cow[MAX_L];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &L);
    scanf("%d %d", &A, &B);
    
    memset(cow, 0, sizeof(cow));
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &S[i], &E[i]);
        cow[S[i]]++;
        cow[E[i] + 1]--;
    }
    
    int count = 0;
    for (int i = 1; i <= L; i++) {
        count += cow[i];
        cow[i] = count > 0;
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    for (int i = 1; i <= L; i++) {
        if (!cow[i]) {
            dp[i] = dp[i-1];
            continue;
        }
        
        for (int j = A; j <= B; j++) {
            if (i - j < 0) break;
            int left = max(0, i - 2*j);
            dp[i] = min(dp[i], dp[left] + 1);
        }
    }
    
    if (dp[L] > N) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[L]);
    }
    
    return 0;
}