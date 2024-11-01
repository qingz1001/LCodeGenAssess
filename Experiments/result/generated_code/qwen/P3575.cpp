#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_S 100

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int l[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &l[i]);
    }

    int d[MAX_S];
    for (int i = 0; i < s; i++) {
        scanf("%d", &d[i]);
    }

    for (int i = 0; i < s; i++) {
        int total_distance = 0;
        for (int j = 0; j < n; j++) {
            total_distance += l[j];
        }
        if (total_distance <= d[i]) {
            printf("1\n");
        } else {
            int max_range = d[i];
            int segments = 0;
            for (int j = 0; j < n; j++) {
                if (l[j] > max_range) {
                    printf("NIE\n");
                    goto next_plane;
                }
                if (l[j] == max_range) {
                    segments++;
                    max_range = d[i];
                } else {
                    max_range -= l[j];
                }
            }
            if (max_range >= l[0]) {
                segments++;
            } else {
                printf("NIE\n");
                goto next_plane;
            }
            printf("%d\n", segments);
next_plane:;
        }
    }

    return 0;
}