#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int value;
    int index;
} Pair;

int compare(const void* a, const void* b) {
    return ((Pair*)a)->value - ((Pair*)b)->value;
}

long long minCost(int arr[], int n) {
    Pair pairs[MAX_N];
    for (int i = 0; i < n; i++) {
        pairs[i].value = arr[i];
        pairs[i].index = i;
    }

    qsort(pairs, n, sizeof(Pair), compare);

    int visited[MAX_N] = {0};
    long long total_cost = 0;

    for (int i = 0; i < n; i++) {
        if (visited[i] || pairs[i].index == i) {
            continue;
        }

        int cycle_size = 0;
        long long cycle_sum = 0;
        int j = i;

        while (!visited[j]) {
            visited[j] = 1;
            cycle_size++;
            cycle_sum += pairs[j].value;
            j = pairs[j].index;
        }

        total_cost += cycle_sum * (cycle_size - 1);
    }

    return total_cost;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long result = minCost(arr, n);
    printf("%lld\n", result);

    return 0;
}