#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来表示每个建筑物
typedef struct {
    int start;
    int end;
    int height;
} Building;

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    Building *buildingA = (Building *)a;
    Building *buildingB = (Building *)b;
    if (buildingA->start == buildingB->start) {
        return buildingA->end - buildingB->end;
    }
    return buildingA->start - buildingB->start;
}

int main() {
    int N;
    scanf("%d", &N);

    Building buildings[N];
    int totalArea = 0;

    // 读取输入
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &buildings[i].start, &buildings[i].end, &buildings[i].height);
    }

    // 按起始位置排序，如果起始位置相同则按结束位置排序
    qsort(buildings, N, sizeof(Building), compare);

    // 计算总覆盖面积
    int currentEnd = 0;
    int maxHeight = 0;

    for (int i = 0; i < N; i++) {
        if (buildings[i].start > currentEnd) {
            totalArea += maxHeight * (buildings[i].start - currentEnd);
            currentEnd = buildings[i].end;
            maxHeight = buildings[i].height;
        } else if (buildings[i].height > maxHeight) {
            totalArea += maxHeight * (buildings[i].end - buildings[i].start);
            maxHeight = buildings[i].height;
            currentEnd = buildings[i].end;
        } else if (buildings[i].end > currentEnd) {
            totalArea += maxHeight * (buildings[i].end - currentEnd);
            currentEnd = buildings[i].end;
        }
    }

    printf("%d\n", totalArea);
    return 0;
}