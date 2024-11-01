#include <stdio.h>
#include <math.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    double towers[M];
    for (int i = 0; i < M; i++) {
        scanf("%lf", &towers[i]);
    }
    
    double min_radius = 0.0;
    double max_radius = 1e6;
    
    while (max_radius - min_radius > 1e-4) {
        double mid_radius = (min_radius + max_radius) / 2.0;
        
        int can_see_all = 1;
        for (int i = 0; i < M; i++) {
            if (i == 0) {
                if (towers[i] - mid_radius < 0) {
                    can_see_all = 0;
                    break;
                }
            } else if (i == M - 1) {
                if (towers[i] + mid_radius > N) {
                    can_see_all = 0;
                    break;
                }
            } else {
                if ((towers[i] - mid_radius < towers[i - 1]) || (towers[i] + mid_radius > towers[i + 1])) {
                    can_see_all = 0;
                    break;
                }
            }
        }
        
        if (can_see_all) {
            max_radius = mid_radius;
        } else {
            min_radius = mid_radius;
        }
    }
    
    printf("%.2f\n", (min_radius + max_radius) / 2.0);
    
    return 0;
}