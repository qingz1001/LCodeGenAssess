#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 1e9

typedef struct {
    int type;
    int l, r;
    long long x;
} Operation;

int n, q;
long long a[MAXN];
Operation ops[MAXN];

void update(int i, long long val) {
    if (val > a[i]) {
        a[i] = val;
    }
}

long long maxSubarraySum(long long arr[], int size) {
    long long max_so_far = 0, max_ending_here = 0;
    for (int i = 0; i < size; i++) {
        max_ending_here += arr[i];
        if (max_ending_here < 0) {
            max_ending_here = 0;
        } else if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
    }
    return max_so_far;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &ops[i].type, &ops[i].l, &ops[i].r);
        if (ops[i].type == 0) {
            scanf("%lld", &ops[i].x);
        }
    }

    for (int i = 0; i < q; i++) {
        if (ops[i].type == 0) {
            update(ops[i].l - 1, ops[i].x);
        } else {
            printf("%lld\n", maxSubarraySum(&a[ops[i].l - 1], ops[i].r - ops[i].l + 1));
        }
    }

    return 0;
}