#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int main() {
    int N, cards[MAX_N], sum = 0, avg, moves = 0;
    
    // 读取输入
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &cards[i]);
        sum += cards[i];
    }
    
    // 计算平均值
    avg = sum / N;
    
    // 计算最少移动次数
    int diff = 0;
    for (int i = 0; i < N - 1; i++) {
        diff += cards[i] - avg;
        if (diff != 0) {
            moves++;
        }
    }
    
    // 输出结果
    printf("%d\n", moves);
    
    return 0;
}