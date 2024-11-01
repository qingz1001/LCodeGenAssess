#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, a, b;
    int w[MAX_N];
    long long total_time = 0;
    long long machine_time = 0;

    scanf("%d %d %d", &n, &a, &b);

    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    qsort(w, n, sizeof(int), compare);

    for (int i = 0; i < n; i++) {
        long long natural_time = (w[i] + a - 1) / a;
        if (natural_time > machine_time) {
            total_time += natural_time;
            machine_time = natural_time;
        } else {
            long long additional_time = (w[i] - machine_time * a + a + b - 1) / (a + b);
            if (additional_time > 0) {
                machine_time += additional_time;
                total_time += additional_time;
            }
        }
    }

    printf("%lld\n", total_time);

    return 0;
}