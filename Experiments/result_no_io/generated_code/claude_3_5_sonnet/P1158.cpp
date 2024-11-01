#include <stdio.h>
#include <math.h>

#define MAX_N 100000

int x1, y1, x2, y2;
int N;
int x[MAX_N], y[MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dist2(int x1, int y1, int x2, int y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

int main() {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    int r1_max = 0, r2_max = 0;
    for (int i = 0; i < N; i++) {
        int d1 = dist2(x1, y1, x[i], y[i]);
        int d2 = dist2(x2, y2, x[i], y[i]);
        r1_max = max(r1_max, d1);
        r2_max = max(r2_max, d2);
    }
    
    int result = min(r1_max, r2_max);
    for (int i = 0; i < N; i++) {
        int d1 = dist2(x1, y1, x[i], y[i]);
        int d2 = dist2(x2, y2, x[i], y[i]);
        result = min(result, max(d1, r2_max));
        result = min(result, max(r1_max, d2));
    }
    
    printf("%d\n", result);
    
    return 0;
}