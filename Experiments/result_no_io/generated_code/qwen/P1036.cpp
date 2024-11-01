#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_X 5000000
#define MAX_SUM (MAX_X * 3)

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void subsets_sum(int arr[], int n, int k, int sum, bool selected[], int count, int *prime_count) {
    if (count == k) {
        if (is_prime(sum)) (*prime_count)++;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!selected[i]) {
            selected[i] = true;
            subsets_sum(arr, n, k, sum + arr[i], selected, count + 1, prime_count);
            selected[i] = false;
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

    bool selected[MAX_N] = {false};
    int prime_count = 0;

    subsets_sum(arr, n, k, 0, selected, 0, &prime_count);

    printf("%d\n", prime_count);

    return 0;
}