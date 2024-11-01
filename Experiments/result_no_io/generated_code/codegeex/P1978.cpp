#include <stdio.h>
#include <stdbool.h>

bool is_valid(int x, int k) {
    if (x % k == 0) {
        return false;
    }
    return true;
}

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);

    long long a[100001];
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    long long ans = 0;
    for (long long i = 0; i < n; i++) {
        if (is_valid(a[i], k)) {
            ans++;
        }
    }

    printf("%lld\n", ans);
    return 0;
}