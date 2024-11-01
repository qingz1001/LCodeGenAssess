#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 2147483648LL
#define MAX_W 100005
#define MAX_K 11

typedef long long ll;

int N, M, W, k;
int x[MAX_W], y[MAX_W];
int cnt[MAX_K][MAX_W];
ll pow2[MAX_K];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void count_trees() {
    int i, j;
    for (i = 0; i < W; i++) {
        for (j = 1; j <= k && j <= x[i]; j++) {
            cnt[j][y[i]]++;
        }
    }
}

ll calculate_result() {
    ll result = 0, tmp;
    int i, j, l, r, m;

    for (i = 0; i <= M; i++) {
        tmp = 1;
        for (j = 1; j <= k; j++) {
            l = 0; r = W - 1;
            while (l <= r) {
                m = (l + r) / 2;
                if (y[m] < i) l = m + 1;
                else r = m - 1;
            }
            tmp = tmp * (cnt[j][i] - r) % MOD;
        }
        result = (result + tmp * (N + 1 - k)) % MOD;
    }

    for (i = k; i <= N; i++) {
        tmp = 1;
        for (j = 1; j <= k; j++) {
            l = 0; r = W - 1;
            while (l <= r) {
                m = (l + r) / 2;
                if (x[m] < i - j + 1) l = m + 1;
                else r = m - 1;
            }
            tmp = tmp * (r - l + 1) % MOD;
        }
        result = (result + tmp * (M + 1)) % MOD;
    }

    return result;
}

int main() {
    int i;
    scanf("%d %d", &N, &M);
    scanf("%d", &W);
    for (i = 0; i < W; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    scanf("%d", &k);

    qsort(x, W, sizeof(int), cmp);
    qsort(y, W, sizeof(int), cmp);

    count_trees();

    pow2[0] = 1;
    for (i = 1; i < MAX_K; i++) {
        pow2[i] = pow2[i-1] * 2 % MOD;
    }

    printf("%lld\n", calculate_result());

    return 0;
}