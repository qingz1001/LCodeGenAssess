#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);

    int *clothes = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &clothes[i]);
    }

    int time = 0;
    while (1) {
        int max_wet = 0;
        for (int i = 0; i < n; i++) {
            if (clothes[i] > max_wet) {
                max_wet = clothes[i];
            }
        }
        if (max_wet <= a) {
            break;
        }
        for (int i = 0; i < n; i++) {
            if (clothes[i] > a) {
                clothes[i] -= b;
            }
        }
        time++;
    }

    printf("%d\n", time);
    free(clothes);
    return 0;
}