#include <stdio.h>
#include <math.h>

int main() {
    double H, S1, V, L, K, n;
    scanf("%lf %lf %lf %lf %lf %lf", &H, &S1, &V, &L, &K, &n);

    int count = 0;
    double g = 10.0;

    // 计算小球下落时间
    double t = sqrt(2 * H / g);

    // 计算小球落地后的位置
    double landing_position = S1 - V * t;

    // 遍历所有小球的位置
    for (int i = 0; i < n; i++) {
        // 判断小球是否落在小车的范围内
        if (landing_position >= i && landing_position <= i + L) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}