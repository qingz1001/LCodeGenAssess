#include <stdio.h>
#include <math.h>

#define MAX_N 100000

int x1, y1, x2, y2;
int n;
int x[MAX_N], y[MAX_N];

int main() {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    int min_cost = 2000000000; // 初始化为一个较大的值
    
    for (int r1 = 0; r1 <= 2000; r1++) {
        int r2 = 0;
        for (int i = 0; i < n; i++) {
            int d1 = (x[i] - x1) * (x[i] - x1) + (y[i] - y1) * (y[i] - y1);
            int d2 = (x[i] - x2) * (x[i] - x2) + (y[i] - y2) * (y[i] - y2);
            if (d1 > r1 * r1) {
                r2 = fmax(r2, (int)ceil(sqrt(d2)));
            }
        }
        int cost = r1 * r1 + r2 * r2;
        if (cost < min_cost) {
            min_cost = cost;
        }
    }
    
    printf("%d\n", min_cost);
    
    return 0;
}