#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    double x1, y1, x2, y2;
    double sx, sy, tx, ty;
    double v;
    
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    }
    
    scanf("%lf %lf", &sx, &sy);
    scanf("%lf %lf", &tx, &ty);
    scanf("%lf", &v);
    
    double distance = sqrt((tx - sx) * (tx - sx) + (ty - sy) * (ty - sy));
    printf("%.6f\n", distance / v);
    
    return 0;
}