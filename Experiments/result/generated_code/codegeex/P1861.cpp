#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int Ini[N][M], Fin[N][M];
    
    // 读取初态
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &Ini[i][j]);
        }
    }
    
    // 读取终态
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &Fin[i][j]);
        }
    }
    
    int total_mana = 0;
    
    // 遍历每个格子，计算魔力
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (Ini[i][j] > Fin[i][j]) {
                // 计算魔力：魔力等于初态与终态的差异乘以间隔
                total_mana += (Ini[i][j] - Fin[i][j]) * ((i + j) % 2);
            }
        }
    }
    
    printf("%d\n", total_mana);
    
    return 0;
}