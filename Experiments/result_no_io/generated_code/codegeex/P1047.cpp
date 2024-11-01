#include <stdio.h>

int main() {
    int l, m;
    scanf("%d %d", &l, &m);

    // 初始化树的数量
    int treeCount = l + 1;

    // 处理每个区域
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // 计算需要移走的树的数量
        int removedTrees = v - u + 1;

        // 更新树的数量
        treeCount -= removedTrees;
    }

    // 输出剩余的树的数量
    printf("%d\n", treeCount);

    return 0;
}