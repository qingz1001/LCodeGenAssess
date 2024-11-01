#include <stdio.h>
#include <math.h>

#define MAX_N 5000
#define MAX_T 2000000

int main() {
    int n, t;
    double a;
    int lights[MAX_T + 1] = {0};
    int max_light = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lf %d", &a, &t);
        for (int j = 1; j <= t; j++) {
            int light = (int)floor(j * a);
            lights[light] ^= 1;
            if (light > max_light) {
                max_light = light;
            }
        }
    }

    for (int i = 1; i <= max_light; i++) {
        if (lights[i]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}