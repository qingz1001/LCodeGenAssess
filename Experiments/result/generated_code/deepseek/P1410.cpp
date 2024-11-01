#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000

int can_partition(int arr[], int n) {
    if (n % 2 != 0) return 0;
    int half = n / 2;
    int dp[MAXN][2];
    dp[0][0] = dp[0][1] = -1;

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i][1] = -1;
        for (int j = 0; j < i; j++) {
            if (dp[j][0] != -1 && arr[j] < arr[i]) {
                dp[i][0] = j;
            }
            if (dp[j][1] != -1 && arr[j] > arr[i]) {
                dp[i][1] = j;
            }
        }
        if (dp[i][0] == -1 && dp[i][1] == -1) return 0;
    }

    return dp[n-1][0] != -1 || dp[n-1][1] != -1;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        int arr[MAXN];
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        if (can_partition(arr, N)) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
    }
    return 0;
}