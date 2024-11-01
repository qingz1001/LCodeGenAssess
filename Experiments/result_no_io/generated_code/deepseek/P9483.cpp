#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long weight;
    long long wear;
} BookStack;

int compare(const void *a, const void *b) {
    return (*(BookStack *)a).weight - (*(BookStack *)b).weight;
}

long long min_cost(int n, long long *weights) {
    if (n == 1) return 0;

    BookStack stacks[n];
    for (int i = 0; i < n; i++) {
        stacks[i].weight = weights[i];
        stacks[i].wear = 0;
    }

    qsort(stacks, n, sizeof(BookStack), compare);

    long long total_cost = 0;
    while (n > 1) {
        int min1 = 0, min2 = 1;
        if (stacks[min1].weight > stacks[min2].weight) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < n; i++) {
            if (stacks[i].weight < stacks[min1].weight) {
                min2 = min1;
                min1 = i;
            } else if (stacks[i].weight < stacks[min2].weight) {
                min2 = i;
            }
        }

        long long new_weight = stacks[min1].weight + stacks[min2].weight;
        long long new_wear = 2 * (stacks[min1].wear > stacks[min2].wear ? stacks[min1].wear : stacks[min2].wear) + 1;
        total_cost += new_weight + new_wear;

        stacks[min1].weight = new_weight;
        stacks[min1].wear = new_wear;

        for (int i = min2; i < n - 1; i++) {
            stacks[i] = stacks[i + 1];
        }
        n--;
    }

    return total_cost;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        long long weights[n];
        for (int i = 0; i < n; i++) {
            scanf("%lld", &weights[i]);
        }
        printf("%lld\n", min_cost(n, weights));
    }
    return 0;
}