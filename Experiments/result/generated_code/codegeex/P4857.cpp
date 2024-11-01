#include <stdio.h>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long a[100001];
    for (int i = 0; i < k; i++) {
        scanf("%lld", &a[i]);
    }

    long long ans[100001] = {0};
    long long max_a = 0;
    for (int i = 0; i < k; i++) {
        if (a[i] > max_a) {
            max_a = a[i];
        }
    }

    long long current_position = 0;
    long long current_command = 0;
    while (current_position < n) {
        long long min_a = LLONG_MAX;
        int min_index = -1;
        for (int i = 0; i < k; i++) {
            if (a[i] != 0 && a[i] < min_a) {
                min_a = a[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            break;
        }

        ans[min_index] += current_command + 1;
        a[min_index] += min_a;
        current_position += min_a;
        current_command++;
    }

    for (int i = 0; i < k; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");

    return 0;
}