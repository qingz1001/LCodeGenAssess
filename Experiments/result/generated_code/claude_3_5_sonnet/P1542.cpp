#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 200000

typedef struct {
    int x, y, s;
} Point;

Point points[MAX_N + 1];
int n;

int check(double speed) {
    double time = 0;
    for (int i = 1; i <= n; i++) {
        time += points[i].s / speed;
        if (time > points[i].y) return 0;
        if (time < points[i].x) time = points[i].x;
    }
    return 1;
}

double binary_search() {
    double left = 0, right = 1e8;
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
        scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].s);
    }
    
    double result = binary_search();
    printf("%.2f\n", result);
    
    return 0;
}