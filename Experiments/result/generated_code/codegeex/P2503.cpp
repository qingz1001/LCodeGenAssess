#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 25
#define MAXM 7

int n, m;
int a[MAXN];
double avg, sum[MAXN];
double min_sigma = 1e9;

void dfs(int step, int group, double current_sigma) {
    if (step == n) {
        if (group == m) {
            min_sigma = fmin(min_sigma, current_sigma);
        }
        return;
    }

    if (group >= m) {
        return;
    }

    for (int i = 0; i < group; i++) {
        double new_sigma = current_sigma;
        sum[i] += a[step];
        new_sigma -= pow((sum[i] / m) - avg, 2) / m;
        dfs(step + 1, group, new_sigma);
        sum[i] -= a[step];
    }

    sum[group] = a[step];
    dfs(step + 1, group + 1, current_sigma - pow((sum[group] / m) - avg, 2) / m);
    sum[group] = 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    avg = 0;
    for (int i = 0; i < n; i++) {
        avg += a[i];
    }
    avg /= m;

    dfs(0, 0, 0);

    printf("%.2lf\n", sqrt(min_sigma));
    return 0;
}