#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll merge(ll *weights, int n) {
    ll total_cost = 0;
    ll *piles = (ll *)malloc(n * sizeof(ll));
    for (int i = 0; i < n; i++) {
        piles[i] = weights[i];
    }
    int num_piles = n;
    while (num_piles > 1) {
        int min1 = 0, min2 = 1;
        if (piles[min1] > piles[min2]) {
            min1 = 1;
            min2 = 0;
        }
        for (int i = 2; i < num_piles; i++) {
            if (piles[i] < piles[min1]) {
                min2 = min1;
                min1 = i;
            } else if (piles[i] < piles[min2]) {
                min2 = i;
            }
        }
        total_cost += piles[min1] + piles[min2] * 2;
        piles[min1] += piles[min2];
        for (int i = min2; i < num_piles - 1; i++) {
            piles[i] = piles[i + 1];
        }
        num_piles--;
    }
    free(piles);
    return total_cost;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int n;
        scanf("%d", &n);
        ll *weights = (ll *)malloc(n * sizeof(ll));
        for (int j = 0; j < n; j++) {
            scanf("%lld", &weights[j]);
        }
        ll result = merge(weights, n);
        printf("%lld\n", result);
        free(weights);
    }
    return 0;
}