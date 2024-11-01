#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 计算最多能有多少只青蛙过河
    int max_frogs = (n + 1) * (1 << n) + m;

    printf("%d\n", max_frogs);

    return 0;
}