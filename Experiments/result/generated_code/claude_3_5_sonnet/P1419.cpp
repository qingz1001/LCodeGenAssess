#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

double findBestSegment(int n, int S, int T, int a[]) {
    double maxAvg = -1e9;
    double sum[MAX_N + 1] = {0};
    
    // 计算前缀和
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + a[i-1];
    }
    
    // 枚举所有可能的段落
    for (int len = S; len <= T; len++) {
        for (int i = 0; i + len <= n; i++) {
            double avg = (sum[i + len] - sum[i]) / len;
            if (avg > maxAvg) {
                maxAvg = avg;
            }
        }
    }
    
    return maxAvg;
}

int main() {
    int n, S, T;
    int a[MAX_N];
    
    scanf("%d", &n);
    scanf("%d %d", &S, &T);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    double result = findBestSegment(n, S, T, a);
    printf("%.3f\n", result);
    
    return 0;
}