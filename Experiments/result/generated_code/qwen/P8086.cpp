#include <stdio.h>
#include <stdbool.h>

#define MAX_N 10000001

int main() {
    int n;
    scanf("%d", &n);

    bool heard[MAX_N] = {false};
    long long total_time = 0;

    for (int i = 0; i < n; ++i) {
        int x, t;
        scanf("%d %d", &x, &t);
        if (t > 1 && !heard[x]) {
            total_time += t;
            heard[x] = true;
        }
    }

    printf("%lld\n", total_time);

    return 0;
}