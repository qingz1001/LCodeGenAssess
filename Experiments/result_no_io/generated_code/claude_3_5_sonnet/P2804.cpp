#include <stdio.h>
#define MOD 92084931

long long solve(int n, int M, int *arr) {
    long long result = 0;
    long long sum = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        sum += arr[right];
        while (left <= right && sum * 1.0 / (right - left + 1) <= M) {
            sum -= arr[left];
            left++;
        }
        result = (result + right - left + 1) % MOD;
    }

    return result;
}

int main() {
    int n, M;
    scanf("%d %d", &n, &M);

    int arr[200000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long answer = solve(n, M, arr);
    printf("%lld\n", answer);

    return 0;
}