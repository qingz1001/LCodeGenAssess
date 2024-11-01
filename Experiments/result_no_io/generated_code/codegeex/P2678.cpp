#include <stdio.h>

int L, N, M;
int stones[50005];

// 判断在给定的最短跳跃距离x下，是否可以通过移除最多M块岩石实现
int canAchieve(int x) {
    int removed = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            // 第一个石头到起点的距离是否超过x
            if (stones[i] > x) return 0;
        } else {
            // 当前石头与前一个石头之间的距离是否超过x
            if (stones[i] - stones[i-1] > x) return 0;
            // 计算需要移除的石头数量
            while (stones[i] - stones[i-1] < x && i < N - 1) {
                i++;
                removed++;
                if (removed > M) return 0;
            }
        }
    }
    return 1;
}

int main() {
    // 读取输入
    scanf("%d %d %d", &L, &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &stones[i]);
    }

    // 二分查找最短跳跃距离的最大值
    int left = 1, right = L;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (canAchieve(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    // 输出结果
    printf("%d\n", left);
    return 0;
}