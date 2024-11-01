#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    double x1, y1, x2, y2;
    double sx, sy, tx, ty;
    double v;
    
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    scanf("%lf %lf", &sx, &sy);
    scanf("%lf %lf", &tx, &ty);
    scanf("%lf", &v);
    
    double min_time = 0.0;
    
    for (int i = 1; i < n; i++) {
        double nx1, ny1, nx2, ny2;
        scanf("%lf %lf %lf %lf", &nx1, &ny1, &nx2, &ny2);
        
        if (nx1 == x2 && ny1 == y2) {
            double time_to_next = sqrt((nx1 - sx) * (nx1 - sx) + (ny1 - sy) * (ny1 - sy)) / v;
            if (time_to_next > min_time) {
                min_time = time_to_next;
            }
            
            double time_from_next = sqrt((nx2 - tx) * (nx2 - tx) + (ny2 - ty) * (ny2 - ty)) / v;
            if (time_from_next > min_time) {
                min_time = time_from_next;
            }
        } else {
            printf("Invalid input: Rectangles are not adjacent.\n");
            return 1;
        }
        
        x1 = nx1;
        y1 = ny1;
        x2 = nx2;
        y2 = ny2;
    }
    
    printf("%.6f\n", min_time);
    
    return 0;
}