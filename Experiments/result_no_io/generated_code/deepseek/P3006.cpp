#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXK 10005

typedef struct {
    int parent;
    long long cows;
    long long capacity;
} Field;

Field fields[MAXN];
long long max_cows[MAXN];
long long total_cows[MAXN];
int N, K;
int times[MAXK];

void dfs(int node) {
    if (node == 1) {
        max_cows[node] = LLONG_MAX;
        total_cows[node] = fields[node].cows;
        return;
    }

    dfs(fields[node].parent);

    long long transfer = fields[node].cows;
    if (fields[node].capacity < transfer) {
        transfer = fields[node].capacity;
    }

    max_cows[node] = transfer;
    total_cows[node] = transfer;
    total_cows[fields[node].parent] += total_cows[node];
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    scanf("%d %d", &N, &K);

    for (int i = 1; i <= N; i++) {
        scanf("%d %lld %lld", &fields[i].parent, &fields[i].cows, &fields[i].capacity);
    }

    for (int i = 0; i < K; i++) {
        scanf("%d", &times[i]);
    }

    qsort(times, K, sizeof(int), compare);

    for (int i = 2; i <= N; i++) {
        dfs(i);
    }

    int current_time = 0;
    long long current_cows = 0;

    for (int i = 0; i < K; i++) {
        while (current_time < times[i]) {
            current_time++;
            current_cows += total_cows[1];
        }
        printf("%lld\n", current_cows);
    }

    return 0;
}