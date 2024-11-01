#include <stdio.h>
#include <stdlib.h>

#define MAX_M 200000

typedef long long ll;

ll max(ll a, ll b) {
    return a > b ? a : b;
}

int main() {
    int M, D;
    scanf("%d %d", &M, &D);

    ll* nums = (ll*)malloc(MAX_M * sizeof(ll));
    int size = 0;
    ll last_query = 0;

    for (int i = 0; i < M; i++) {
        char op;
        scanf(" %c", &op);

        if (op == 'Q') {
            int L;
            scanf("%d", &L);

            ll max_val = nums[size - 1];
            for (int j = size - 2; j >= size - L; j--) {
                max_val = max(max_val, nums[j]);
            }

            printf("%lld\n", max_val);
            last_query = max_val;
        } else if (op == 'A') {
            ll n;
            scanf("%lld", &n);

            nums[size++] = (n + last_query) % D;
        }
    }

    free(nums);
    return 0;
}