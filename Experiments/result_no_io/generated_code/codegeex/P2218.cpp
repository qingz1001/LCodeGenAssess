#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x, y;
} Tree;

int compare(const void *a, const void *b) {
    Tree *treeA = (Tree *)a;
    Tree *treeB = (Tree *)b;
    if (treeA->x != treeB->x) return treeA->x - treeB->x;
    return treeA->y - treeB->y;
}

int main() {
    int N;
    scanf("%d", &N);
    Tree trees[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &trees[i].x, &trees[i].y);
    }

    qsort(trees, N, sizeof(Tree), compare);

    int minL = INT_MAX;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int L = trees[j].x - trees[i].x;
            if (L < minL) {
                int maxX = INT_MIN, maxY = INT_MIN;
                for (int k = 0; k < N; k++) {
                    if (trees[k].x >= trees[i].x && trees[k].x <= trees[j].x) {
                        maxX = trees[k].x;
                    }
                    if (trees[k].y >= trees[i].y && trees[k].y <= trees[j].y) {
                        maxY = trees[k].y;
                    }
                }
                if (maxX != INT_MIN && maxY != INT_MIN) {
                    int area = (maxX - trees[i].x) * (maxY - trees[i].y);
                    if (area < minL * minL) {
                        minL = area;
                    }
                }
            }
        }
    }

    if (minL == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minL);
    }

    return 0;
}