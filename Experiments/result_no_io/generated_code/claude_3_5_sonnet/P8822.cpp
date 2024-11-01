#include <stdio.h>

int main() {
    int n, v, m, a;
    scanf("%d %d %d %d", &n, &v, &m, &a);

    long long total = 0;
    int price = v;
    int count = 0;

    for (int i = 1; i <= n; i++) {
        total += price;
        count++;
        if (count == m) {
            price += a;
            count = 0;
        }
    }

    printf("%lld\n", total);

    return 0;
}