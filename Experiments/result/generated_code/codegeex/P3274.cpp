#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20001
#define MAXM 200001
#define MAXK 100001

int n, m, k;
int zombies[MAXN][MAXN];
int maxZombies[MAXN];
int track[MAXN];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        zombies[y][x] = 1;
    }
    
    // 计算每条轨道上每个位置的最大僵尸数
    for (int i = 1; i <= n; i++) {
        int max = 0;
        for (int j = 1; j <= n; j++) {
            maxZombies[i] += zombies[i][j];
            if (zombies[i][j]) {
                max = zombies[i][j];
            }
        }
        track[i] = max;
    }
    
    int totalZombies = 0;
    for (int i = 1; i <= n; i++) {
        totalZombies += track[i];
    }
    
    printf("%d %d\n", 1, track[1]);
    
    for (int i = 1; i < k; i++) {
        int max = 0;
        int trackNum = 1;
        for (int j = 1; j <= n; j++) {
            if (track[j] > max) {
                max = track[j];
                trackNum = j;
            }
        }
        printf("%d %d\n", trackNum, max);
        
        // 更新轨道上的僵尸数
        for (int j = 1; j <= n; j++) {
            track[j] = 0;
        }
        
        for (int j = 1; j <= n; j++) {
            for (int l = 1; l <= n; l++) {
                if (zombies[j][l]) {
                    track[j] += 1;
                }
            }
        }
    }
    
    printf("%d\n", totalZombies);
    
    return 0;
}