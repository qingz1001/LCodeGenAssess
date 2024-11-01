#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *w = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    int time = 0;
    while (1) {
        int all_done = 1;
        for (int i = 0; i < m; i++) {
            if (w[i] > 0) {
                all_done = 0;
                w[i]--;
            }
        }
        if (all_done) break;
        time++;
    }

    printf("%d\n", time);

    free(w);
    return 0;
}