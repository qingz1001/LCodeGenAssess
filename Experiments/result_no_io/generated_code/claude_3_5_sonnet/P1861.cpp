#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int N, M;
int Ini[MAX_N][MAX_M];
int Fin[MAX_N][MAX_M];
int Diff[MAX_N][MAX_M];
int RowSum[MAX_N];
int ColSum[MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &Ini[i][j]);
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &Fin[i][j]);
            Diff[i][j] = Fin[i][j] - Ini[i][j];
            RowSum[i] += Diff[i][j];
            ColSum[j] += Diff[i][j];
        }
    }
    
    long long result = 0;
    
    for (int i = 0; i < N; i++) {
        long long rowResult = 0;
        for (int j = 0; j < M; j++) {
            if (Diff[i][j] > 0) {
                rowResult += (long long)j * Diff[i][j];
            }
        }
        for (int j = M - 1; j >= 0; j--) {
            if (Diff[i][j] < 0) {
                rowResult -= (long long)j * Diff[i][j];
            }
        }
        result += rowResult;
    }
    
    for (int j = 0; j < M; j++) {
        long long colResult = 0;
        for (int i = 0; i < N; i++) {
            if (Diff[i][j] > 0) {
                colResult += (long long)i * Diff[i][j];
            }
        }
        for (int i = N - 1; i >= 0; i--) {
            if (Diff[i][j] < 0) {
                colResult -= (long long)i * Diff[i][j];
            }
        }
        result += colResult;
    }
    
    printf("%lld\n", result);
    
    return 0;
}