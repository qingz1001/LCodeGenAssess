#include <stdio.h>
#include <string.h>

#define MAX_N 205
#define MAX_M 205

int N, M, P;
int sum[MAX_N][MAX_M];
int matrix[MAX_N][MAX_M];

void solve() {
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            int s = sum[i][j];
            for (int k = 0; k < P; k++) {
                if ((s - k - matrix[i-1][j] - matrix[i][j-1] + matrix[i-1][j-1]) % P == 0) {
                    matrix[i][j] = k;
                    break;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &P);
    
    memset(sum, 0, sizeof(sum));
    memset(matrix, 0, sizeof(matrix));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &sum[i][j]);
        }
    }
    
    solve();
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", matrix[i][j]);
            if (j < M - 1) printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}