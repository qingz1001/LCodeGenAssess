#include <stdio.h>
#include <math.h>

#define EPS 0.01

int main() {
    int N;
    scanf("%d", &N);
    
    double x[5001], y[5001];
    for (int i = 0; i < N; ++i) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    
    double min_y = y[0];
    for (int i = 1; i < N; ++i) {
        if (y[i] < min_y) {
            min_y = y[i];
        }
    }
    
    printf("%.2f\n", min_y);
    
    return 0;
}