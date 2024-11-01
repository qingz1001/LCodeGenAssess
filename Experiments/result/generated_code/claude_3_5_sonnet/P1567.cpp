#include <stdio.h>

#define MAX_N 1000000

int main() {
    int N;
    int temperatures[MAX_N];
    int max_ascending_days = 1;
    int current_ascending_days = 1;

    // 读取输入
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &temperatures[i]);
    }

    // 计算最长连续上升天数
    for (int i = 1; i < N; i++) {
        if (temperatures[i] > temperatures[i-1]) {
            current_ascending_days++;
            if (current_ascending_days > max_ascending_days) {
                max_ascending_days = current_ascending_days;
            }
        } else {
            current_ascending_days = 1;
        }
    }

    // 输出结果
    printf("%d\n", max_ascending_days);

    return 0;
}