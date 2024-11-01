#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 2147483648LL
#define MAXW 100005
#define MAXK 10

typedef long long ll;

int N, M, W, k;
int trees[MAXW][2];
int row_count[MAXW], col_count[MAXW];
ll comb[MAXW][MAXK];
ll bit[MAXW];

int cmp(const void *a, const void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    if (x[1] == y[1]) return x[0] - y[0];
    return x[1] - y[1];
}

void update(int x, ll v) {
    for (; x < MAXW; x += x & -x) {
        bit[x] = (bit[x] + v) % MOD;
    }
}

ll query(int x) {
    ll sum = 0;
    for (; x > 0; x -= x & -x) {
        sum = (sum + bit[x]) % MOD;
    }
    return sum;
}

ll combination(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (comb[n][r] != -1) return comb[n][r];
    comb[n][r] = (combination(n-1, r) + combination(n-1, r-1)) % MOD;
    return comb[n][r];
}

int main() {
    scanf("%d %d", &N, &M);
    scanf("%d", &W);
    for (int i = 0; i < W; i++) {
        scanf("%d %d", &trees[i][0], &trees[i][1]);
    }
    scanf("%d", &k);

    qsort(trees, W, sizeof(trees[0]), cmp);

    memset(comb, -1, sizeof(comb));
    memset(row_count, 0, sizeof(row_count));
    memset(col_count, 0, sizeof(col_count));
    memset(bit, 0, sizeof(bit));

    for (int i = 0; i < W; i++) {
        row_count[trees[i][0]]++;
        col_count[trees[i][1]]++;
    }

    ll total_sum = 0;
    for (int i = 0; i < W; i++) {
        int x = trees[i][0], y = trees[i][1];
        ll left = combination(row_count[x], k);
        ll right = combination(row_count[x] - 1, k);
        ll up = combination(col_count[y], k);
        ll down = combination(col_count[y] - 1, k);

        ll current_sum = (left * up - right * down) % MOD;
        total_sum = (total_sum + current_sum) % MOD;

        update(y + 1, current_sum);
    }

    printf("%lld\n", (total_sum + MOD) % MOD);
    return 0;
}