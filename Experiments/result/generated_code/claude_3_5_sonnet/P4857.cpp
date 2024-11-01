#include <stdio.h>
#include <stdlib.h>

#define MAX_K 100000

typedef long long ll;

int main() {
    ll n;
    int k;
    scanf("%lld %d", &n, &k);

    int a[MAX_K];
    ll pos[MAX_K] = {0};
    ll last_step[MAX_K] = {0};

    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }

    for (ll step = 1; step <= n; step++) {
        int min_index = 0;
        for (int i = 1; i < k; i++) {
            if (pos[i] < pos[min_index]) {
                min_index = i;
            }
        }

        pos[min_index] += a[min_index];
        last_step[min_index] = step;
    }

    for (int i = 0; i < k; i++) {
        printf("%lld ", last_step[i]);
    }

    return 0;
}