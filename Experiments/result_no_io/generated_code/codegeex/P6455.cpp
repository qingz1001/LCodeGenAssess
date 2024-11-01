#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 100000
#define MAX_K 100000
#define MAX_R 2000
#define MAX_L 100000000

typedef long long ll;

struct Circle {
    int index;
    int position;
};

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    struct Circle *circleA = (struct Circle *)a;
    struct Circle *circleB = (struct Circle *)b;
    return circleA->position - circleB->position;
}

// 计算圆的面积
double calculateArea(int radius) {
    return M_PI * radius * radius;
}

int main() {
    int n, k, r, L;
    scanf("%d%d%d%d", &n, &k, &r, &L);

    struct Circle circles[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &circles[i].position);
        circles[i].index = i + 1;
    }

    // 对圆心位置进行排序
    qsort(circles, n, sizeof(struct Circle), compare);

    // 计算每个圆的面积
    double areas[MAX_N];
    for (int i = 0; i < n; i++) {
        areas[i] = calculateArea(r);
    }

    // 初始化并集面积和选择数组
    double unionArea = 0;
    int selected[MAX_N] = {0};

    // 选择k个圆，使得并面积最大
    for (int i = 0; i < n && k > 0; i++) {
        if (selected[i]) continue;

        // 选择当前圆
        selected[i] = 1;
        unionArea += areas[i];
        k--;

        // 检查并集面积是否超过限制
        if (unionArea > 1e12) break;

        // 检查其他圆是否与当前圆重叠
        for (int j = i + 1; j < n && k > 0; j++) {
            if (selected[j]) continue;

            // 计算两个圆心之间的距离
            int distance = abs(circles[i].position - circles[j].position);
            if (distance <= 2 * r) {
                // 计算重叠面积并更新并集面积
                double overlapArea = calculateArea(r) - calculateArea(2 * r - distance);
                unionArea += overlapArea;
                selected[j] = 1;
                k--;
            }

            // 检查并集面积是否超过限制
            if (unionArea > 1e12) break;
        }
    }

    // 输出选择的圆的编号
    for (int i = 0; i < n; i++) {
        if (selected[i]) {
            printf("%d ", circles[i].index);
        }
    }
    printf("\n");

    return 0;
}