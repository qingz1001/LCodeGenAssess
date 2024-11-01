#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 101
#define MAX_L 10000001
#define INF 0x3f3f3f3f

int L, S, T, M;
int stones[MAX_M];
int dp[MAX_L];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &L);
    scanf("%d %d %d", &S, &T, &M);
    
    for (int i = 1; i <= M; i++) {
        scanf("%d", &stones[i]);
    }
    stones[0] = 0;
    stones[M + 1] = L;
    
    // 对石头位置进行排序
    for (int i = 1; i <= M; i++) {
        for (int j = i + 1; j <= M + 1; j++) {
            if (stones[i] > stones[j]) {
                int temp = stones[i];
                stones[i] = stones[j];
                stones[j] = temp;
            }
        }
    }
    
    // 压缩坐标
    int new_L = 0;
    for (int i = 1; i <= M + 1; i++) {
        int diff = stones[i] - stones[i-1];
        if (diff > T) {
            new_L += T;
        } else {
            new_L += diff;
        }
    }
    
    // 初始化dp数组
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    int stone_index = 1;
    for (int i = 1; i <= new_L; i++) {
        for (int j = S; j <= T && i - j >= 0; j++) {
            dp[i] = min(dp[i], dp[i-j]);
        }
        if (stone_index <= M && i == stones[stone_index] - stones[0]) {
            dp[i]++;
            stone_index++;
        }
    }
    
    int result = INF;
    for (int i = new_L - T; i <= new_L; i++) {
        result = min(result, dp[i]);
    }
    
    printf("%d\n", result);
    
    return 0;
}