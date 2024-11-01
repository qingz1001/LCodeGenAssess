#include <stdio.h>
#include <limits.h>

#define MAX_N 50005
#define MOD 10007

int arr[MAX_N];
int sum[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int check(int n, int m, int x) {
    int count = 1;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i] > x) {
            return 0;
        }
        if (sum + arr[i] > x) {
            count++;
            sum = arr[i];
            if (count > m) {
                return 0;
            }
        } else {
            sum += arr[i];
        }
    }
    return 1;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int max_length = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        max_length = max(max_length, arr[i]);
    }

    int left = 1, right = max_length, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (check(n, m, mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d ", ans);

    int dp[MAX_N] = {0};
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (arr[i] > ans) {
            break;
        }
        for (int j = i; j >= 1; j--) {
            if (sum[i] - sum[j - 1] <= ans) {
                dp[i] = (dp[i] + dp[j - 1]) % MOD;
            }
        }
        sum[i] = sum[i - 1] + arr[i];
    }

    printf("%d\n", dp[n]);
    return 0;
}