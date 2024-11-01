#include <stdio.h>
#include <stdlib.h>

#define MAX_COORD 2000000

// 定义村庄结构体
typedef struct {
    int x;
    int next;
} Village;

// 定义邮局结构体
typedef struct {
    int left;
    int right;
} PostOffice;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Village *villageA = (Village *)a;
    Village *villageB = (Village *)b;
    return villageA->x - villageB->x;
}

// 计算在区间[l, r]内建邮局的最小距离
int calculateMinDistance(Village *villages, int l, int r, int m) {
    if (m == 1) {
        int distance = 0;
        for (int i = l; i <= r; i++) {
            distance += abs(villages[i].x - villages[l].x);
        }
        return distance;
    } else if (m == 2) {
        int mid = (l + r) / 2;
        int distance1 = 0, distance2 = 0;
        for (int i = l; i <= mid; i++) {
            distance1 += abs(villages[i].x - villages[mid].x);
        }
        for (int i = mid + 1; i <= r; i++) {
            distance2 += abs(villages[i].x - villages[mid + 1].x);
        }
        return distance1 + distance2;
    } else {
        int mid = (l + r) / 2;
        int distance1 = calculateMinDistance(villages, l, mid, m - 1);
        int distance2 = calculateMinDistance(villages, mid + 1, r, m - 1);
        return distance1 + distance2;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Village *villages = (Village *)malloc(sizeof(Village) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &villages[i].x);
        villages[i].next = -1;
    }

    // 对村庄进行排序
    qsort(villages, n, sizeof(Village), compare);

    // 计算最小距离
    int minDistance = calculateMinDistance(villages, 0, n - 1, m);

    printf("%d\n", minDistance);

    free(villages);
    return 0;
}