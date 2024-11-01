#include <stdio.h>
#include <string.h>

int main() {
    char grid[200][200];
    int N = 0;
    
    // 读取输入
    while (scanf("%s", grid[N]) != EOF) {
        N++;
    }
    
    // 输出N
    printf("%d ", N);
    
    // 压缩码生成
    int count = 0;
    char current = grid[0][0];
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == current) {
                count++;
            } else {
                printf("%d ", count);
                current = grid[i][j];
                count = 1;
            }
        }
    }
    
    // 输出最后一个计数
    printf("%d\n", count);
    
    return 0;
}