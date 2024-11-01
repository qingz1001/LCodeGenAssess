#include <stdio.h>

#define MOD 92084931

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[200001];
    long long sum[200001] = {0};
    int count = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        sum[i] = sum[i - 1] + arr[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if ((sum[j] - sum[i - 1]) / (j - i + 1) > m) {
                count++;
            }
        }
    }

    printf("%d\n", count % MOD);
    return 0;
}