#include <stdio.h>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long a[k];
    for (long long i = 0; i < k; ++i) {
        scanf("%lld", &a[i]);
    }
    long long commands[k];
    for (long long i = 0; i < k; ++i) {
        commands[i] = n / a[i];
        if (n % a[i] != 0) {
            ++commands[i];
        }
    }
    for (long long i = 0; i < k; ++i) {
        printf("%lld ", commands[i]);
    }
    return 0;
}