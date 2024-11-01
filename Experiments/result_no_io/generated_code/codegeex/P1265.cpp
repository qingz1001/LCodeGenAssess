#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    double x[5000], y[5000];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }

    double total_length = 0;
    for (int i = 0; i < n; i++) {
        double min_distance = 1e9; // 初始化为一个很大的值
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double distance = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
                if (distance < min_distance) {
                    min_distance = distance;
                }
            }
        }
        total_length += min_distance;
    }

    printf("%.2lf\n", total_length);
    return 0;
}