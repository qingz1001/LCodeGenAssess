#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 40

int n;
int lengths[MAX_N];

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// 计算三角形面积
double calculate_area(int a, int b, int c) {
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    // 对木板长度进行降序排序
    qsort(lengths, n, sizeof(int), cmp);

    double max_area = 0;
    int found = 0;

    // 尝试所有可能的三边组合
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (lengths[i] < lengths[j] + lengths[k]) {
                    double area = calculate_area(lengths[i], lengths[j], lengths[k]);
                    if (area > max_area) {
                        max_area = area;
                        found = 1;
                    }
                    break;  // 找到一个有效组合后，跳出最内层循环
                }
            }
            if (found) break;  // 找到有效组合后，跳出第二层循环
        }
        if (found) break;  // 找到有效组合后，跳出最外层循环
    }

    if (found) {
        printf("%d\n", (int)(max_area * 100));
    } else {
        printf("-1\n");
    }

    return 0;
}