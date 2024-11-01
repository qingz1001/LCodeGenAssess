#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来存储每个植株的花生数目及其坐标
typedef struct {
    int x, y, peanuts;
} Plant;

// 比较函数，用于按花生数目从大到小排序
int compare(const void *a, const void *b) {
    Plant *plantA = (Plant *)a;
    Plant *plantB = (Plant *)b;
    return plantB->peanuts - plantA->peanuts;
}

int main() {
    int M, N, K;
    scanf("%d%d%d", &M, &N, &K);

    // 计算从路边跳到路边的时间
    int jumpTime = 2 * (N - 1);

    // 如果时间不够跳到路边，直接输出0
    if (jumpTime > K) {
        printf("0\n");
        return 0;
    }

    // 减去跳到路边的时间
    K -= jumpTime;

    // 动态分配数组存储植株信息
    Plant *plants = (Plant *)malloc(M * N * sizeof(Plant));
    int plantCount = 0;

    // 读取花生田信息
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int peanuts;
            scanf("%d", &peanuts);
            if (peanuts > 0) {
                plants[plantCount].x = i;
                plants[plantCount].y = j;
                plants[plantCount].peanuts = peanuts;
                plantCount++;
            }
        }
    }

    // 按花生数目从大到小排序
    qsort(plants, plantCount, sizeof(Plant), compare);

    int totalPeanuts = 0;
    int currentTime = 0;

    // 依次采摘花生
    for (int i = 0; i < plantCount; i++) {
        int startX = plants[i].x;
        int startY = plants[i].y;
        int nextTime = currentTime + startX + abs(startY - plants[i - 1].y) + 1; // 跳到下一个植株的时间

        if (nextTime > K) {
            break;
        }

        currentTime = nextTime;
        totalPeanuts += plants[i].peanuts;
    }

    printf("%d\n", totalPeanuts);

    // 释放动态分配的内存
    free(plants);

    return 0;
}