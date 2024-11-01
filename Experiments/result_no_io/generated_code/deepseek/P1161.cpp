#include <stdio.h>
#include <stdlib.h>

#define MAX_T 2000000

int main() {
    int n;
    scanf("%d", &n);

    int *lights = (int *)calloc(MAX_T + 1, sizeof(int));
    if (lights == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        double a;
        int t;
        scanf("%lf %d", &a, &t);

        for (int j = 1; j <= t; j++) {
            int index = (int)(j * a);
            lights[index]++;
        }
    }

    for (int i = 0; i <= MAX_T; i++) {
        if (lights[i] % 2 == 1) {
            printf("%d\n", i);
            break;
        }
    }

    free(lights);
    return 0;
}