#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main() {
    int n;
    ll a, b;
    scanf("%d %lld %lld", &n, &a, &b);

    ll *left = (ll *)malloc(n * sizeof(ll));
    ll *right = (ll *)malloc(n * sizeof(ll));

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &left[i], &right[i]);
    }

    ll max_reward = -1;

    for (int i = 0; i < n; i++) {
        ll product = 1;
        for (int j = 0; j < i; j++) {
            product *= left[j];
        }
        ll reward = product / right[i];
        if (reward > max_reward) {
            max_reward = reward;
        }
    }

    printf("%lld\n", max_reward);

    free(left);
    free(right);

    return 0;
}