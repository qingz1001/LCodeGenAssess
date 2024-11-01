#include <stdio.h>
#include <stdbool.h>

int L, N, M;
int stones[50005];

bool canRemove(int maxDist) {
    int removed = 0;
    for (int i = 0; i < N; i++) {
        if (stones[i] - stones[i-1] < maxDist) {
            removed++;
            if (removed > M) return false;
        }
    }
    return true;
}

int main() {
    // 读取输入
    scanf("%d%d%d", &L, &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &stones[i]);
    }
    stones[N] = L; // 添加终点

    // 二分查找最大最短跳跃距离
    int left = 1, right = L;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (canRemove(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    // 输出结果
    printf("%d\n", left);
    return 0;
}