#include <stdio.h>
#include <stdlib.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int *stations = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &stations[i]);
        }

        int *count = (int *)calloc(n + 1, sizeof(int));
        for (int i = 0; i < n; i++) {
            count[stations[i]]++;
        }

        int min_stations = 0;
        for (int i = 1; i <= n; i++) {
            if (count[i] > 2) {
                min_stations += count[i] - 2;
            }
        }

        printf("%d\n", min_stations);

        free(stations);
        free(count);
    }
    return 0;
}