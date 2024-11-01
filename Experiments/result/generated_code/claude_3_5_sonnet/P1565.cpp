#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int N, M;
long long a[MAX_N][MAX_M];
long long prefix_sum[MAX_N + 1][MAX_M + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    
    // Calculate prefix sum
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            prefix_sum[i][j] = prefix_sum[i-1][j] + prefix_sum[i][j-1] - prefix_sum[i-1][j-1] + a[i-1][j-1];
        }
    }
    
    int max_area = 0;
    
    // Enumerate all possible rectangles
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int k = i; k <= N; k++) {
                for (int l = j; l <= M; l++) {
                    long long sum = prefix_sum[k][l] - prefix_sum[i-1][l] - prefix_sum[k][j-1] + prefix_sum[i-1][j-1];
                    int area = (k - i + 1) * (l - j + 1);
                    if (sum > 0) {
                        max_area = max(max_area, area);
                    }
                }
            }
        }
    }
    
    printf("%d\n", max_area);
    
    return 0;
}