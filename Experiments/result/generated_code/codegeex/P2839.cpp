#include <stdio.h>
#include <stdlib.h>

// 定义节点结构体，用于存储数组元素及其索引
typedef struct {
    int val;
    int idx;
} Node;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    return nodeA->val - nodeB->val;
}

int main() {
    int n, q;
    scanf("%d", &n);

    // 定义数组
    int a[n];
    Node nodes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        nodes[i].val = a[i];
        nodes[i].idx = i;
    }

    // 对数组进行排序
    qsort(nodes, n, sizeof(Node), compare);

    // 定义查询结果数组
    int results[n];
    for (int i = 0; i < n; i++) {
        results[nodes[i].idx] = i;
    }

    scanf("%d", &q);

    int last_answer = 0;
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a = (a + last_answer) % n;
        b = (b + last_answer) % n;
        c = (c + last_answer) % n;
        d = (d + last_answer) % n;

        // 确保a < b < c < d
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        if (b > c) {
            int temp = b;
            b = c;
            c = temp;
        }
        if (c > d) {
            int temp = c;
            c = d;
            d = temp;
        }

        // 查找最大中位数
        int max_median = -1;
        for (int j = a; j <= b; j++) {
            int median_idx = results[j];
            if (median_idx >= c && median_idx <= d) {
                max_median = a[j];
            }
        }

        printf("%d\n", max_median);
        last_answer = max_median;
    }

    return 0;
}