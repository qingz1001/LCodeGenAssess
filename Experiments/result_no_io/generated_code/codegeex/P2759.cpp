#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    double x = 1.0;
    while (true) {
        double power = pow(x, x);
        if (power >= pow(10, n - 1)) {
            printf("%.0f\n", x);
            break;
        }
        x += 0.1;
    }

    return 0;
}