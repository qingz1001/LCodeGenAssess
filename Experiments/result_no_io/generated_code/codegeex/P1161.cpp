#include <stdio.h>

#define MAX_T 2000000
#define MAX_N 5000

int lights[MAX_T + 1];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        double a;
        int t;
        scanf("%lf %d", &a, &t);

        for (int j = 1; j <= t; j++) {
            int index = (int)(a * j);
            lights[index] = 1 - lights[index];
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