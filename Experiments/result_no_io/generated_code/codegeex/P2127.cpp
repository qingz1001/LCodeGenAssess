#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int pos;
} Pair;

int cmp(const void *a, const void *b) {
    Pair *pa = (Pair *)a;
    Pair *pb = (Pair *)b;
    return pa->val - pb->val;
}

long long minCost(int *arr, int n) {
    Pair *pairs = (Pair *)malloc(n * sizeof(Pair));
    for (int i = 0; i < n; i++) {
        pairs[i].val = arr[i];
        pairs[i].pos = i;
    }
    qsort(pairs, n, sizeof(Pair), cmp);

    int *pos = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        pos[pairs[i].pos] = i;
    }

    long long cost = 0;
    for (int i = 0; i < n; i++) {
        if (pos[i] != i) {
            int target = pairs[i].val;
            int targetPos = pos[i];
            int temp = arr[i];
            arr[i] = target;
            arr[targetPos] = temp;
            cost += (long long)arr[i] + arr[targetPos];
        }
    }

    free(pairs);
    free(pos);
    return cost;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long result = minCost(arr, n);
    printf("%lld\n", result);

    free(arr);
    return 0;
}