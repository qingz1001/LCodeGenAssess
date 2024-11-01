#include <stdio.h>
#include <math.h>

#define MAX_N 100005

double a[MAX_N];
double sum[MAX_N];
double sqrsum[MAX_N];

void update(int x, int y, double k) {
    sum[x] += k;
    sqrsum[x] += 2 * k * (a[x] + k / 2);
    a[x] += k;
    if (y < MAX_N - 1) {
        sum[y + 1] -= k;
        sqrsum[y + 1] -= 2 * k * (a[y + 1] - k / 2);
    }
}

double get_average(int x, int y) {
    double total = sum[y] - (x > 0 ? sum[x - 1] : 0);
    return total / (y - x + 1);
}

double get_variance(int x, int y) {
    int n = y - x + 1;
    double avg = get_average(x, y);
    double total_sqr = sqrsum[y] - (x > 0 ? sqrsum[x - 1] : 0);
    return total_sqr / n - avg * avg;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lf", &a[i]);
        sum[i] = (i > 0 ? sum[i - 1] : 0) + a[i];
        sqrsum[i] = (i > 0 ? sqrsum[i - 1] : 0) + a[i] * a[i];
    }

    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        x--; y--;  // 转换为0-based索引

        if (op == 1) {
            double k;
            scanf("%lf", &k);
            update(x, y, k);
        } else if (op == 2) {
            printf("%.4f\n", get_average(x, y));
        } else if (op == 3) {
            printf("%.4f\n", get_variance(x, y));
        }
    }

    return 0;
}