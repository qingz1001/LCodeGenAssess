#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

typedef struct {
    long long x, y, s;
} Point;

Point points[MAX_N + 1];
int n;

int check(double speed) {
    double current_time = 0;
    for (int i = 1; i <= n; i++) {
        current_time += points[i].s / speed;
        if (current_time > points[i].y) return 0;
        if (current_time < points[i].x) current_time = points[i].x;
    }
    return 1;
}

double binary_search() {
    double left = 0, right = 1e9;
    while (right - left > 1e-7) {
        double mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid;
    }
    return left;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld %lld", &points[i].x, &points[i].y, &points[i].s);
    }
    
    double result = binary_search();
    printf("%.2f\n", result);
    
    return 0;
}