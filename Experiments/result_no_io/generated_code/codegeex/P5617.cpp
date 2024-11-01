#include <stdio.h>
#include <math.h>

#define EPS 1e-8
#define PI 3.14159265358979323846

typedef long long ll;

int n, k, r;
ll x[100005];

// 计算圆的面积
double circle_area(double radius) {
    return PI * radius * radius;
}

// 计算两个圆的交面积
double intersection_area(double r1, double r2, double d) {
    double d2 = d * d;
    double r1sq = r1 * r1;
    double r2sq = r2 * r2;
    if (d >= r1 + r2) return 0;
    if (d <= fabs(r1 - r2)) {
        if (r1 > r2) return circle_area(r2);
        else return circle_area(r1);
    }
    double x = (d2 + r1sq - r2sq) / (2 * d);
    double f = sqrt(r1sq - x * x);
    return f * (d - x) + PI * (r1sq - x * x);
}

// 计算前缀交面积和
double prefix_intersection_area(int i) {
    double area = 0;
    for (int j = 0; j < i; ++j) {
        area += intersection_area(r, r, x[i] - x[j]);
    }
    return area;
}

int main() {
    // 读取输入
    scanf("%d %d %d", &n, &k, &r);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &x[i]);
    }

    // 计算前缀交面积和
    double prefix_areas[100005];
    for (int i = 0; i < n; ++i) {
        prefix_areas[i] = prefix_intersection_area(i);
    }

    // 计算答案
    double max_area = 0;
    for (int i = 0; i <= n - k; ++i) {
        double area = circle_area(r * k) - prefix_areas[i] - (n - k - i) * circle_area(r);
        if (area > max_area) {
            max_area = area;
        }
    }

    // 输出答案
    printf("%.9lf\n", max_area);

    return 0;
}