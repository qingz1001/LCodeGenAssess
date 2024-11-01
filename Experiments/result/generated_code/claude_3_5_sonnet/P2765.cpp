#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 55
#define MAX_BALLS 3000

int n, totalBalls;
int poles[MAX_N][MAX_BALLS];
int poleSize[MAX_N];

bool isSquare(int num) {
    int i;
    for (i = 1; i * i <= num; i++) {
        if (i * i == num) return true;
    }
    return false;
}

void dfs(int ball) {
    int i, j;
    for (i = 0; i < n; i++) {
        if (poleSize[i] == 0 || isSquare(ball + poles[i][poleSize[i] - 1])) {
            poles[i][poleSize[i]++] = ball;
            totalBalls++;
            dfs(ball + 1);
            poleSize[i]--;
            totalBalls--;
        }
    }
}

int main() {
    scanf("%d", &n);
    
    dfs(1);
    
    printf("%d\n", totalBalls);
    
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < poleSize[i]; j++) {
            printf("%d ", poles[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}