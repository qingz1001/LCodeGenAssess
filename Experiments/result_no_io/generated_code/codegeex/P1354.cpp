#include <stdio.h>
#include <math.h>

#define INF 999999999

int main() {
    int n;
    scanf("%d", &n);

    double x[n+1], a1[n], b1[n], a2[n], b2[n];

    // 输入墙的信息
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf %lf", &x[i], &a1[i], &b1[i], &a2[i], &b2[i]);
    }

    // 添加入口和出口的虚拟墙
    x[n] = 10.0;
    a1[n] = 0.0;
    b1[n] = 5.0;
    a2[n] = 5.0;
    b2[n] = 10.0;

    // 初始化距离数组
    double dist[21][21];
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            dist[i][j] = INF;
        }
    }

    // 初始化入口到墙的缺口距离
    for (int i = 0; i <= n; i++) {
        dist[5][i] = fabs(x[i] - 0.0);
    }

    // 计算每堵墙之间的距离
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double min_dist = INF;
            if (x[i] != x[j]) {
                min_dist = fabs(x[i] - x[j]);
            } else {
                min_dist = fmin(fabs(a1[i] - a1[j]), fmin(fabs(b1[i] - a1[j]), fmin(fabs(a1[i] - b1[j]), fabs(b1[i] - b1[j]))));
            }
            dist[i][j] = min_dist;
        }
    }

    // 使用Floyd-Warshall算法计算最短路径
    for (int k = 0; k <= n; k++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 输出最短距离
    printf("%.2lf\n", dist[0][n]);

    return 0;
}