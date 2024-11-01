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

        // 计算最少换乘站的数量
        int min_stations = n;
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (stations[j] == stations[i]) {
                    count++;
                }
            }
            if (count > 2) {
                min_stations -= count - 2;
            }
        }

        printf("%d\n", min_stations);
        free(stations);
    }
    return 0;
}