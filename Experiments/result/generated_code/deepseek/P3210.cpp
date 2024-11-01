#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll max(ll a, ll b) {
    return a > b ? a : b;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    ll *a = (ll *)malloc(N * sizeof(ll));
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }

    ll first_sum = 0, second_sum = 0;
    int turn = 0; // 0 for first player, 1 for second player

    for (int i = 0; i < N; i++) {
        if (a[i] == 0) continue;

        int j = i;
        while (j < N && a[j] != 0) j++;

        ll sum = 0;
        for (int k = i; k < j; k++) {
            sum += a[k];
        }

        if (turn == 0) {
            first_sum += max(a[i], a[j - 1]);
        } else {
            second_sum += max(a[i], a[j - 1]);
        }

        turn = 1 - turn;
        i = j - 1;
    }

    printf("%lld %lld\n", first_sum, second_sum);

    free(a);
    return 0;
}