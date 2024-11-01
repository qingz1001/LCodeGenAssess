#include <stdio.h>
#include <string.h>

#define MAX_N 501
#define MAX_M 501

int N, M;
int height[MAX_N][MAX_M];
int can_build[MAX_N][MAX_M];

void dfs(int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= M || can_build[i][j]) return;
    can_build[i][j] = 1;
    
    if (i > 0 && height[i-1][j] > height[i][j]) dfs(i-1, j);
    if (i < N-1 && height[i+1][j] > height[i][j]) dfs(i+1, j);
    if (j > 0 && height[i][j-1] > height[i][j]) dfs(i, j-1);
    if (j < M-1 && height[i][j+1] > height[i][j]) dfs(i, j+1);
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    
    memset(can_build, 0, sizeof(can_build));
    
    int count = 0;
    for (int j = 0; j < M; j++) {
        if (!can_build[0][j]) {
            dfs(0, j);
            count++;
        }
    }
    
    int impossible = 0;
    for (int j = 0; j < M; j++) {
        if (!can_build[N-1][j]) {
            impossible++;
        }
    }
    
    if (impossible == 0) {
        printf("1\n%d\n", count);
    } else {
        printf("0\n%d\n", impossible);
    }
    
    return 0;
}