#include <stdio.h>

int main() {
    int v, n, c;
    scanf("%d %d %d", &v, &n, &c);

    int k, m;
    int total_volume = 0;
    int total_effort = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &k, &m);
        total_volume += k;
        total_effort += m;
    }

    if (total_volume < v) {
        printf("Impossible\n");
    } else {
        int remaining_effort = total_effort - (v - total_volume) * c;
        if (remaining_effort >= 0) {
            printf("%d\n", remaining_effort);
        } else {
            printf("Impossible\n");
        }
    }

    return 0;
}