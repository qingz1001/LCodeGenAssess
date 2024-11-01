#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);

    int up[21] = {0, a, a};  // 上车人数
    int down[21] = {0, 0, 0};  // 下车人数
    int onboard[21] = {0, a, a};  // 车上人数

    // 计算每站上下车人数
    for (int i = 3; i < n; i++) {
        up[i] = up[i-1] + up[i-2];
        down[i] = up[i-1];
        onboard[i] = onboard[i-1] + up[i] - down[i];
    }

    // 计算最后一站下车人数
    down[n] = m;
    
    // 计算倒数第二站上车人数
    up[n-1] = m - down[n-1];

    // 更新倒数第二站车上人数
    onboard[n-1] = onboard[n-2] + up[n-1] - down[n-1];

    // 输出x站开出时车上的人数
    printf("%d\n", onboard[x]);

    return 0;
}