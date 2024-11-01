#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MOD 2147483648

typedef struct {
    int x, y;
} Node;

int cmp(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    if (nodeA->x == nodeB->x) {
        return nodeA->y - nodeB->y;
    }
    return nodeA->x - nodeB->x;
}

int main() {
    int n, m, w, k;
    scanf("%d %d %d", &n, &m, &w);
    Node *trees = (Node *)malloc(w * sizeof(Node));
    for (int i = 0; i < w; i++) {
        scanf("%d %d", &trees[i].x, &trees[i].y);
    }
    scanf("%d", &k);

    qsort(trees, w, sizeof(Node), cmp);

    ll result = 0;

    // 计算虔诚度总和
    for (int i = 0; i < w; i++) {
        int x = trees[i].x;
        int y = trees[i].y;

        // 计算上方和下方的树木数量
        int upCount = 0, downCount = 0;
        for (int j = 0; j < w; j++) {
            if (trees[j].y < y) {
                upCount++;
            } else if (trees[j].y > y) {
                downCount++;
            }
        }

        // 计算左右两侧的树木数量
        int leftCount = 0, rightCount = 0;
        for (int j = 0; j < w; j++) {
            if (trees[j].x < x) {
                leftCount++;
            } else if (trees[j].x > x) {
                rightCount++;
            }
        }

        // 判断是否满足虔诚度条件
        if (upCount >= k && downCount >= k && leftCount >= k && rightCount >= k) {
            result += (ll)upCount * downCount * leftCount * rightCount;
            result %= MOD;
        }
    }

    printf("%lld\n", result);
    free(trees);
    return 0;
}