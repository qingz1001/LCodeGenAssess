#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 800
#define MAX_N 1000

typedef struct {
    int x, y;
} Tower;

Tower towers[MAX_M];
int n, m;

int compare(const void *a, const void *b) {
    return ((Tower*)a)->x - ((Tower*)b)->x;
}

double distance(Tower a, Tower b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double max(double a, double b) {
    return a > b ? a : b;
}

double min_radius() {
    double left = 0, right = 200000, mid;
    int i;
    
    while (right - left > 1e-5) {
        mid = (left + right) / 2;
        double last_y = 0;
        int valid = 1;
        
        for (i = 0; i < m && valid; i++) {
            double y = towers[i].y - sqrt(mid * mid - (towers[i].x - towers[i-1].x) * (towers[i].x - towers[i-1].x) / 4.0);
            if (y > last_y) last_y = y;
            else valid = 0;
        }
        
        if (valid && last_y >= 0) right = mid;
        else left = mid;
    }
    
    return left;
}

int main() {
    scanf("%d %d", &n, &m);
    
    int i;
    for (i = 0; i < m; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
    }
    
    qsort(towers, m, sizeof(Tower), compare);
    
    double result = min_radius();
    printf("%.2f\n", result);
    
    return 0;
}