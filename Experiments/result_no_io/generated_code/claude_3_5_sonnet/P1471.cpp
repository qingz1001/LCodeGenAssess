#include <stdio.h>
#include <math.h>

#define MAX_N 100005

double arr[MAX_N];
double sum[MAX_N];
double sqsum[MAX_N];

void update(int x, int y, double k) {
    sum[x] += k;
    sqsum[x] += 2 * k * (arr[x] + k / 2);
    arr[x] += k;
    if (y < MAX_N - 1) {
        sum[y + 1] -= k;
        sqsum[y + 1] -= 2 * k * (arr[y + 1] - k / 2);
    }
}

double get_avg(int x, int y) {
    double total_sum = sum[y] - (x > 0 ? sum[x - 1] : 0);
    return total_sum / (y - x + 1);
}

double get_variance(int x, int y) {
    int n = y - x + 1;
    double avg = get_avg(x, y);
    double total_sqsum = sqsum[y] - (x > 0 ? sqsum[x - 1] : 0);
    return total_sqsum / n - avg * avg;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%lf", &arr[i]);
        sum[i] = (i > 0 ? sum[i - 1] : 0) + arr[i];
        sqsum[i] = (i > 0 ? sqsum[i - 1] : 0) + arr[i] * arr[i];
    }

    for (int i = 0; i < M; i++) {
        int op, x, y;
        double k;
        scanf("%d %d %d", &op, &x, &y);
        x--; y--;  // Convert to 0-based index

        if (op == 1) {
            scanf("%lf", &k);
            update(x, y, k);
        } else if (op == 2) {
            printf("%.4f\n", get_avg(x, y));
        } else if (op == 3) {
            printf("%.4f\n", get_variance(x, y));
        }
    }

    return 0;
}