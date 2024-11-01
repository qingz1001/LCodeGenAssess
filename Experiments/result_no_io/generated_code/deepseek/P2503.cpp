#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAXN 20
#define MAXM 6

int n, m;
int a[MAXN];
int groups[MAXM];
double min_variance = INT_MAX;

void calculate_variance() {
    int sum = 0;
    for (int i = 0; i < m; i++) {
        sum += groups[i];
    }
    double mean = (double)sum / m;
    double variance = 0.0;
    for (int i = 0; i < m; i++) {
        variance += (groups[i] - mean) * (groups[i] - mean);
    }
    variance /= m;
    if (variance < min_variance) {
        min_variance = variance;
    }
}

void dfs(int index, int group_index) {
    if (index == n) {
        calculate_variance();
        return;
    }
    for (int i = 0; i < m; i++) {
        groups[i] += a[index];
        dfs(index + 1, i);
        groups[i] -= a[index];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        groups[i] = 0;
    }

    dfs(0, 0);

    printf("%.2f\n", sqrt(min_variance));

    return 0;
}