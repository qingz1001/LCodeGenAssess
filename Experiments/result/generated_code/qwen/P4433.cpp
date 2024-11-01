#include <stdio.h>

#define MOD 1000000007

typedef struct {
    long long a;
    long long b;
} Operation;

long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    Operation operations[q];
    for (int i = 0; i < q; i++) {
        scanf("%d", &operations[i].a);
        if (operations[i].a == 1) {
            scanf("%lld %lld %lld %lld", &operations[i].b, &operations[i].c, &operations[i].d, &operations[i].e);
        } else {
            scanf("%lld %lld", &operations[i].b, &operations[i].c);
        }
    }

    long long result = 0;
    for (int i = 0; i < q; i++) {
        if (operations[i].a == 1) {
            long long l = operations[i].b;
            long long r = operations[i].c;
            long long a = operations[i].d;
            long long b = operations[i].e;
            long long sum = ((r - l + 1) * a * modInverse(r - l + 1, b)) % b;
            result += sum;
        } else {
            long long l = operations[i].b;
            long long r = operations[i].c;
            printf("%lld\n", (result + (l - 1) * (l - 2) / 2) % MOD);
        }
    }

    return 0;
}