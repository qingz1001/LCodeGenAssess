#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 5000
#define MAX_T 2000000

int lights[MAX_T + 1] = {0};

int main() {
    int n, t;
    double a;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lf %d", &a, &t);
        for (int j = 1; j <= t; j++) {
            int index = (int)floor(j * a);
            if (index > MAX_T) break;
            lights[index] ^= 1;
        }
    }

    for (int i = 1; i <= MAX_T; i++) {
        if (lights[i]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}