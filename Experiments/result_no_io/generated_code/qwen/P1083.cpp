#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *rooms = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &rooms[i]);
    }

    int *days = (int *)malloc(m * sizeof(int));
    int *starts = (int *)malloc(m * sizeof(int));
    int *ends = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &days[i], &starts[i], &ends[i]);
    }

    for (int i = 0; i < m; i++) {
        int d = days[i];
        int s = starts[i];
        int t = ends[i];

        int can_satisfy = 1;
        for (int j = s - 1; j <= t - 1; j++) {
            if (rooms[j] < d) {
                can_satisfy = 0;
                break;
            }
            rooms[j] -= d;
        }

        if (!can_satisfy) {
            printf("-1\n%d\n", i + 1);
            free(rooms);
            free(days);
            free(starts);
            free(ends);
            return 0;
        }
    }

    printf("0\n");
    free(rooms);
    free(days);
    free(starts);
    free(ends);
    return 0;
}