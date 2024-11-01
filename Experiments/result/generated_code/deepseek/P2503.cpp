#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 20
#define MAXM 6

int n, m;
int a[MAXN];
int group[MAXN];
double min_variance = 1e9;

double calculate_variance() {
    int sum[MAXM] = {0};
    for (int i = 0; i < n; i++) {
        sum[group[i]] += a[i];
    }
    double total_sum = 0;
    for (int i = 0; i < m; i++) {
        total_sum += sum[i];
    }
    double mean = total_sum / m;
    double variance = 0;
    for (int i = 0; i < m; i++) {
        variance += (sum[i] - mean) * (sum[i] - mean);
    }
    return variance / m;
}

void dfs(int index, int groups_used) {
    if (index == n) {
        if (groups_used == m) {
            double variance = calculate_variance();
            if (variance < min_variance) {
                min_variance = variance;
            }
        }
        return;
    }
    for (int i = 0; i < groups_used; i++) {
        group[index] = i;
        dfs(index + 1, groups_used);
    }
    if (groups_used < m) {
        group[index] = groups_used;
        dfs(index + 1, groups_used + 1);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    dfs(0, 0);
    printf("%.2f\n", sqrt(min_variance));
    return 0;
}