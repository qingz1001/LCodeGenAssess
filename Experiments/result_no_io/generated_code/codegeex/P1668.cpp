#include <stdio.h>
#include <stdlib.h>

#define MAX_T 1000001
#define MAX_N 25001

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    int start[MAX_N], end[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }

    // 使用差分数组来记录每个时间段的需求
    int demand[MAX_T] = {0};
    for (int i = 0; i < N; i++) {
        demand[start[i]]++;
        if (end[i] < T) {
            demand[end[i]]--;
        }
    }

    // 计算前缀和，得到每个时间段的实际需求
    int current = 0;
    int max_demand = 0;
    for (int i = 1; i <= T; i++) {
        current += demand[i];
        if (current > 0) {
            max_demand = current;
        }
    }

    // 如果最大需求超过奶牛数量，则无法满足
    if (max_demand > N) {
        printf("-1\n");
    } else {
        printf("%d\n", N - max_demand);
    }

    return 0;
}