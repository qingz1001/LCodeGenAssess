#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Bowl {
    int h;
    int r1;
    int r2;
} bowls[10];

int compare(const void *a, const void *b) {
    struct Bowl * bowlA = (struct Bowl *)a;
    struct Bowl * bowlB = (struct Bowl *)b;
    
    // 计算碗的体积
    double volumeA = M_PI * bowlA->r1 * bowlA->r1 * bowlA->h;
    double volumeB = M_PI * bowlB->r1 * bowlB->r1 * bowlB->h;
    
    // 按体积排序
    if (volumeA < volumeB) return -1;
    if (volumeA > volumeB) return 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }
    
    // 按碗的体积排序
    qsort(bowls, n, sizeof(struct Bowl), compare);
    
    int height = 0;
    int currentHeight = 0;
    
    for (int i = 0; i < n; i++) {
        // 如果当前碗可以放在最上面，更新高度
        if (currentHeight == 0 || bowls[i].r2 <= bowls[i-1].r1) {
            currentHeight += bowls[i].h;
        } else {
            // 否则更新堆叠的最大高度
            height = currentHeight > height ? currentHeight : height;
            currentHeight = bowls[i].h;
        }
    }
    
    // 最后一个碗的高度
    height = currentHeight > height ? currentHeight : height;
    
    printf("%d\n", height);
    
    return 0;
}