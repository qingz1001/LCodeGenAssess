#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main() {
    int N;
    scanf("%d", &N);

    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    int points[N][2];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    // 计算长方形框子的长和宽
    int length = abs(x2 - x1);
    int width = abs(y2 - y1);

    // 计算框子的总面积
    int total_area = length * width;

    // 初始化最大面积和最小半径
    double max_area = 0;
    double min_radius = 0;

    // 遍历所有点，计算油滴扩展后的面积
    for (int i = 0; i < N; i++) {
        int x = points[i][0];
        int y = points[i][1];

        // 计算油滴扩展的最大半径
        double max_r = fmin(fmin(x - x1, x2 - x), fmin(y - y1, y2 - y));

        // 计算油滴扩展后的面积
        double area = PI * max_r * max_r;

        // 更新最大面积和最小半径
        if (area > max_area) {
            max_area = area;
            min_radius = max_r;
        }
    }

    // 计算剩余的最小空间
    int remaining_area = total_area - (int)(max_area + 0.5);

    // 输出结果
    printf("%d\n", remaining_area);

    return 0;
}