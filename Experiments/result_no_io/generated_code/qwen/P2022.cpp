#include <stdio.h>
#include <stdlib.h>

int count(int n) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        char str[20];
        sprintf(str, "%d", i);
        cnt += strlen(str);
    }
    return cnt;
}

int main() {
    long long k, m;
    scanf("%lld %lld", &k, &m);

    if (m < k) {
        printf("0\n");
        return 0;
    }

    long long low = 1, high = 1e9 + 1;
    while (low < high) {
        long long mid = (low + high) / 2;
        if (count(mid) >= m) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    if (count(low) == m) {
        printf("%lld\n", low);
    } else {
        printf("0\n");
    }

    return 0;
}