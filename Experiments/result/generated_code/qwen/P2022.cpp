#include <stdio.h>

long long Q(long long N) {
    if (N <= 9)
        return N;
    long long len = 1, count = 9, sum = 0;
    while (sum + count * len < N) {
        sum += count * len;
        count *= 10;
        len++;
    }
    N -= sum;
    long long num = pow(10, len - 1) + (N - 1) / len;
    int pos = (N - 1) % len;
    return (num / (int)pow(10, len - pos - 1)) % 10;
}

int main() {
    long long K, M;
    scanf("%lld %lld", &K, &M);
    if (M == 1) {
        printf("1\n");
        return 0;
    }
    if (K == 1) {
        printf("%lld\n", M);
        return 0;
    }
    long long left = 1, right = 1e18;
    while (left < right) {
        long long mid = (left + right) / 2;
        if (Q(mid) >= M) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    if (Q(left) != M)
        printf("0\n");
    else
        printf("%lld\n", left);
    return 0;
}