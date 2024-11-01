#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 10000
#define MAXD 100000

int N, T_max;
int d[MAXN];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

bool can_finish_in_time(int K) {
    int time = 0;
    int stage[K];
    for (int i = 0; i < K; i++) {
        stage[i] = d[i];
    }
    qsort(stage, K, sizeof(int), compare);

    for (int i = K; i < N; i++) {
        time = stage[0];
        stage[0] = d[i];
        qsort(stage, K, sizeof(int), compare);
    }

    for (int i = 0; i < K; i++) {
        if (time + stage[i] > T_max) {
            return false;
        }
        time += stage[i];
    }
    return true;
}

int binary_search_K() {
    int left = 1, right = N;
    while (left < right) {
        int mid = (left + right) / 2;
        if (can_finish_in_time(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &T_max);
    for (int i = 0; i < N; i++) {
        scanf("%d", &d[i]);
    }

    int result = binary_search_K();
    printf("%d\n", result);

    return 0;
}