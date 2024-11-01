#include <stdio.h>

int main() {
    double s, a, b;
    scanf("%lf %lf %lf", &s, &a, &b);

    // 计算两人同时到达B地所需的最短时间
    // 时间 = (总距离 - 甲步行时间) / 车的速度
    // 甲步行时间 = 甲步行速度 * 时间
    // 乙步行时间 = 乙步行速度 * 时间
    // 由于甲乙步行速度相同，所以时间 = 总距离 / (车速度 - 甲步行速度)
    double time = s / (b - a);

    printf("%.6lf\n", time);
    return 0;
}