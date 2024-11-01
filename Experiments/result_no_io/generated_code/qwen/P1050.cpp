#include <stdio.h>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);

    if (k == 1) {
        printf("-1\n");
        return 0;
    }

    long long current = n % (long long)pow(10, k);
    long long original = current;
    int length = 0;

    do {
        current = (current * n) % (long long)pow(10, k);
        length++;
    } while (current != original && length < k * k);

    if (length == k * k) {
        printf("-1\n");
    } else {
        printf("%d\n", length);
    }

    return 0;
}