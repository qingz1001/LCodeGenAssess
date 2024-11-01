#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化最大青蛙数为河心石墩数和荷叶数之和
    int max_frogs = n + m;

    // 如果荷叶数大于石墩数，则最多青蛙数为石墩数的两倍加上荷叶数
    if (m > n) {
        max_frogs = 2 * n + m;
    }

    printf("%d\n", max_frogs);
    return 0;
}