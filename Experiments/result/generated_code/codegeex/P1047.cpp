#include <stdio.h>

int main() {
    int l, m;
    scanf("%d %d", &l, &m);

    // 初始化树的数量为马路的长度加1（包括起点和终点）
    int trees = l + 1;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // 计算需要移走的树的数量
        int removed_trees = v - u + 1;

        // 更新树的数量
        trees -= removed_trees;
    }

    // 输出剩余的树的数量
    printf("%d\n", trees);

    return 0;
}