#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000
#define MAX_NM 1000000

long long x0, a, b, c, d;
int N, M, Q;
int T[MAX_NM + 1];
int board[MAX_N][MAX_M];
int path[MAX_N + MAX_M];

long long nextRandom() {
    static long long x = x0;
    x = (a * x * x + b * x + c) % d;
    return x;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void generatePermutation() {
    for (int i = 1; i <= N * M; i++) {
        T[i] = i;
    }
    
    for (int i = 1; i <= N * M; i++) {
        int j = (nextRandom() % i) + 1;
        swap(&T[i], &T[j]);
    }
    
    for (int i = 0; i < Q; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        swap(&T[u], &T[v]);
    }
}

void fillBoard() {
    int k = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            board[i][j] = T[k++];
        }
    }
}

void findPath() {
    int dp[MAX_N][MAX_M];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = board[0][0];
    
    for (int i = 1; i < N; i++) {
        dp[i][0] = (dp[i-1][0] < board[i][0]) ? board[i][0] : dp[i-1][0];
    }
    
    for (int j = 1; j < M; j++) {
        dp[0][j] = (dp[0][j-1] < board[0][j]) ? board[0][j] : dp[0][j-1];
    }
    
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            int min_prev = (dp[i-1][j] < dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
            dp[i][j] = (min_prev < board[i][j]) ? board[i][j] : min_prev;
        }
    }
    
    int i = N - 1, j = M - 1, k = N + M - 2;
    while (i >= 0 && j >= 0) {
        path[k--] = dp[i][j];
        if (i > 0 && dp[i-1][j] == dp[i][j]) {
            i--;
        } else {
            j--;
        }
    }
}

int main() {
    scanf("%lld %lld %lld %lld %lld", &x0, &a, &b, &c, &d);
    scanf("%d %d %d", &N, &M, &Q);
    
    generatePermutation();
    fillBoard();
    findPath();
    
    for (int i = 0; i < N + M - 1; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
    
    return 0;
}