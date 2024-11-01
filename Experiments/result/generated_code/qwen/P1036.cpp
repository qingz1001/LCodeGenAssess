#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_K 20
#define MAX_SUM 15000000 // 5 * 10^6 * 3

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void combination_sum(int arr[], int n, int k, int start, int sum, bool visited[], int count[]) {
    if (count[sum]) return;
    if (k == 0) {
        if (is_prime(sum)) {
            count[sum]++;
        }
        return;
    }
    for (int i = start; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            combination_sum(arr, n, k - 1, i + 1, sum + arr[i], visited, count);
            visited[i] = false;
        }
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bool visited[MAX_N] = {false};
    int count[MAX_SUM] = {0};

    combination_sum(arr, n, k, 0, 0, visited, count);

    int result = 0;
    for (int i = 0; i < MAX_SUM; i++) {
        if (count[i] > 0) {
            result++;
        }
    }

    printf("%d\n", result);

    return 0;
}