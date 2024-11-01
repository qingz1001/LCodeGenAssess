#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

typedef long long ll;

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    int arr[MAXN], sorted[MAXN];
    ll cost = 0;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        sorted[i] = arr[i];
    }

    qsort(sorted, N, sizeof(int), cmp);

    int pos[MAXN];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i] == sorted[j]) {
                pos[i] = j;
                break;
            }
        }
    }

    int visited[MAXN] = {0};
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int cycle_size = 0;
            int j = i;
            ll cycle_sum = 0;
            int min_in_cycle = 1e9;

            while (!visited[j]) {
                visited[j] = 1;
                cycle_sum += arr[j];
                if (arr[j] < min_in_cycle) min_in_cycle = arr[j];
                j = pos[j];
                cycle_size++;
            }

            if (cycle_size > 1) {
                ll cost1 = cycle_sum + (cycle_size - 2) * min_in_cycle;
                ll cost2 = cycle_sum + min_in_cycle + (cycle_size + 1) * sorted[0];
                cost += (cost1 < cost2) ? cost1 : cost2;
            }
        }
    }

    printf("%lld\n", cost);
    return 0;
}