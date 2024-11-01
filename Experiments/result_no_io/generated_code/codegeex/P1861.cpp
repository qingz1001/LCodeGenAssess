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
    
    int total_magic = 0;
    
    // 遍历每个格子，计算魔力
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (Ini[i][j] > Fin[i][j]) {
                int stars_to_move = Ini[i][j] - Fin[i][j];
                for (int k = 0; k < stars_to_move; k++) {
                    total_magic += (k + 1);
                }
            }
        }
    }
    
    printf("%d\n", total_magic);
    
    return 0;
}