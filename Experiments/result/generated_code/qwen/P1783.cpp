#include <stdio.h>
#include <math.h>

#define EPS 1e-6

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    double towers[M];
    for (int i = 0; i < M; i++) {
        scanf("%lf", &towers[i]);
    }
    
    double left = 0.0, right = 100000.0;
    while (right - left > EPS) {
        double mid = (left + right) / 2.0;
        int covered = 0;
        
        for (int i = 0; i < M; i++) {
            if (i == 0 && towers[i] <= mid) covered++;
            else if (i > 0 && towers[i] - towers[i - 1] <= mid * 2) covered++;
        }
        
        if (covered == M) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    printf("%.2f\n", (left + right) / 2.0);
    return 0;
}