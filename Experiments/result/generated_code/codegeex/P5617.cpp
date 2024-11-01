#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

int n, k, r;
double x[100005], ans = 0.0;

int main() {
    // 读取输入
    scanf("%d%d%d", &n, &k, &r);
    for (int i = 1; i <= n; i++) scanf("%lf", &x[i]);

    // 计算所有圆的面积总和
    for (int i = 1; i <= n; i++) {
        ans += PI * r * r;
    }

    // 如果选出的圆数为 n，直接输出总面积
    if (k == n) {
        printf("%.10lf\n", ans);
        return 0;
    }

    // 计算需要删除的圆数
    int del = n - k;

    // 计算需要删除的圆的最小距离
    double min_dist = x[1] + r;
    for (int i = 2; i <= n; i++) {
        min_dist = fmin(min_dist, x[i] - x[i - 1] - 2 * r);
    }

    // 计算删除一个圆后增加的面积
    double added_area = PI * r * r - 0.25 * PI * (min_dist + 2 * r) * (min_dist + 2 * r);

    // 更新答案
    ans -= added_area * del;

    // 输出结果
    printf("%.10lf\n", ans);
    return 0;
}