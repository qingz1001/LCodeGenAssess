#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    long long result = 1;
    for (int i = 0; i < n - 1; ++i) {
        result = (result * m) % p;
    }

    printf("%lld\n", result);
    return 0;
}