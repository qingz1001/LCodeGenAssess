#include <stdio.h>

#define MOD 92084931

int main() {
    int n, M;
    scanf("%d %d", &n, &M);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            if (sum * 1.0 / (j - i + 1) > M) {
                count++;
            }
        }
    }

    printf("%d\n", count % MOD);
    return 0;
}