#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int power_mod(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    char n[MAX_LEN];
    int k;
    scanf("%s %d", n, &k);

    int mod = 1;
    for (int i = 0; i < k; i++)
        mod *= 10;

    int base = 0;
    for (int i = 0; n[i]; i++)
        base = (base * 10 + n[i] - '0') % mod;

    int cycle_len = 1;
    int current = base;
    while (cycle_len <= mod) {
        current = power_mod(base, cycle_len + 1, mod);
        if (current == base)
            break;
        cycle_len++;
    }

    if (cycle_len > mod)
        printf("-1\n");
    else
        printf("%d\n", cycle_len);

    return 0;
}