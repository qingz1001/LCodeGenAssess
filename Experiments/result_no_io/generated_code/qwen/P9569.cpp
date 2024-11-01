#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, T;
    scanf("%d %d", &n, &T);

    int *vi = (int *)malloc(n * sizeof(int));
    int *ti = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &vi[i], &ti[i]);
    }

    int max_height = 0;
    int min_index = -1;

    for (int t = 0; t <= T; t++) {
        for (int i = 0; i < n; i++) {
            if (t >= ti[i]) {
                int height = vi[i] * (t - ti[i]);
                if (height > max_height) {
                    max_height = height;
                    min_index = i + 1;
                }
            } else {
                int height = vi[i] * t;
                if (height > max_height) {
                    max_height = height;
                    min_index = i + 1;
                }
            }
        }
    }

    printf("%d\n", min_index);

    free(vi);
    free(ti);

    return 0;
}