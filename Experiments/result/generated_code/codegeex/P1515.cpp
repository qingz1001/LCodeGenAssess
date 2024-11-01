#include <stdio.h>

int main() {
    int A, B, N, m, count = 0;
    int hotels[20] = {990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};

    // 读取输入
    scanf("%d %d %d", &A, &B, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &m);
        hotels[i] = m;
    }

    // 计算旅行方案数
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (hotels[i] - hotels[j] >= A && hotels[i] - hotels[j] <= B) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}