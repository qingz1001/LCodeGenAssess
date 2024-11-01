#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 青蛙总数计算公式：荷叶数 * 2 + 石墩数 + 1
    // 荷叶数 * 2 是因为每片荷叶最多可以站两只青蛙（一只青蛙在上面，一只青蛙在下面）
    // 石墩数是因为每座石墩最多可以站一只青蛙
    // 加1是因为初始时有一只青蛙直接站在石墩上
    int total_frogs = m * 2 + n + 1;

    printf("%d\n", total_frogs);

    return 0;
}