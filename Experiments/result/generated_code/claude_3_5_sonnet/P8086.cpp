#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 10000001

int main() {
    int n;
    scanf("%d", &n);

    long long total_time = 0;
    bool* listened = (bool*)calloc(MAX_N, sizeof(bool));

    for (int i = 0; i < n; i++) {
        int x, t;
        scanf("%d %d", &x, &t);

        if (t > 1 && !listened[x]) {
            total_time += t;
            listened[x] = true;
        }
    }

    printf("%lld\n", total_time);

    free(listened);
    return 0;
}