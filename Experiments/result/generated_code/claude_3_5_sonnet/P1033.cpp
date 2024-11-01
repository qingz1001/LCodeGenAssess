#include <stdio.h>
#include <math.h>

#define g 10.0
#define EPSILON 0.0001

int main() {
    double H, S1, V, L, K;
    int n;
    scanf("%lf %lf %lf %lf %lf %d", &H, &S1, &V, &L, &K, &n);

    int count = 0;
    for (int i = 0; i < n; i++) {
        double t = sqrt(2 * (H - K) / g);
        double S2 = S1 + V * t;
        double ballPosition = i;

        if (ballPosition >= S2 - EPSILON && ballPosition <= S2 + L + EPSILON) {
            count++;
        } else if (ballPosition > S2 + L) {
            break;
        }
    }

    printf("%d\n", count);
    return 0;
}