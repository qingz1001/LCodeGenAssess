#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, a, b;
    int w[MAX_N];
    long long total_wetness = 0;
    int max_wetness = 0;

    scanf("%d %d %d", &n, &a, &b);

    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
        total_wetness += w[i];
        if (w[i] > max_wetness) {
            max_wetness = w[i];
        }
    }

    qsort(w, n, sizeof(int), cmp);

    long long time = 0;
    long long dried = 0;

    for (int i = 0; i < n; i++) {
        long long current_time = (w[i] + a + b - 1) / (a + b);
        if (current_time > time) {
            time = current_time;
        }
        dried += time * a;
    }

    long long remaining = total_wetness - dried;
    if (remaining > 0) {
        time += (remaining + b - 1) / b;
    }

    printf("%lld\n", time);

    return 0;
}