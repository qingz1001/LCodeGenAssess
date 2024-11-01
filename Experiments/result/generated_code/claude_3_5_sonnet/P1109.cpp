#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50

int main() {
    int n, L, R;
    int students[MAX_N];
    int total_students = 0;
    int moves = 0;

    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
        total_students += students[i];
    }
    scanf("%d %d", &L, &R);

    // 检查是否有解
    if (total_students < n * L || total_students > n * R) {
        printf("-1\n");
        return 0;
    }

    // 计算最少移动次数
    for (int i = 0; i < n; i++) {
        if (students[i] < L) {
            moves += L - students[i];
        } else if (students[i] > R) {
            moves += students[i] - R;
        }
    }

    // 输出结果
    printf("%d\n", moves / 2);

    return 0;
}