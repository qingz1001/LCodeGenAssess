#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50000

struct Point {
    double x, y;
};

struct Point misha[MAXN], nadia[MAXN];

double distance(struct Point a, struct Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double find_min_time(int n, int m) {
    double min_time = INFINITY;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double time = distance(misha[i], nadia[j]);
            if (time > min_time) continue;
            double max_time = fmax(distance(misha[i], misha[n-1]), distance(nadia[j], nadia[m-1]));
            if (time <= max_time) {
                min_time = fmin(min_time, time);
            }
        }
    }
    return min_time == INFINITY ? -1 : min_time;
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &misha[i].x, &misha[i].y);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &nadia[i].x, &nadia[i].y);
    }
    double min_time = find_min_time(n, m);
    if (min_time == -1) {
        printf("impossible\n");
    } else {
        printf("%.5lf\n", min_time);
    }
    return 0;
}