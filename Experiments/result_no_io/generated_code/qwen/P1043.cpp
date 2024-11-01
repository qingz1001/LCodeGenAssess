#include <stdio.h>
#include <stdlib.h>

#define MOD 10

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void find_min_max(int *nums, int n, int m, int *min_val, int *max_val) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
    }
    *min_val = (*min_val + sum) % MOD;
    *max_val = (*max_val + sum) % MOD;

    if (m == 1) {
        *min_val = (*min_val + nums[0]) % MOD;
        *max_val = (*max_val + nums[n - 1]) % MOD;
    } else {
        *min_val = (*min_val + nums[0]) % MOD;
        *max_val = (*max_val + nums[n - 1]) % MOD;
        for (int i = 1; i < n; i++) {
            *min_val = min(*min_val, (sum - nums[i - 1] + nums[i]) % MOD);
            *max_val = max(*max_val, (sum - nums[i - 1] + nums[i]) % MOD);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int min_val = 0, max_val = 0;
    find_min_max(nums, n, m, &min_val, &max_val);

    printf("%d\n%d\n", min_val, max_val);

    free(nums);
    return 0;
}