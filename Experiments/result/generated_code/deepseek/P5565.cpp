#include <stdio.h>
#include <string.h>

#define MOD 998244353

typedef long long ll;

ll mod_add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mod_sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mod_mul(ll a, ll b) {
    return (a * b) % MOD;
}

ll mod_pow(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = mod_mul(result, base);
        }
        base = mod_mul(base, base);
        exp /= 2;
    }
    return result;
}

ll mod_inv(ll a) {
    return mod_pow(a, MOD - 2);
}

ll calculate_harmony(char *expression, int len) {
    // Placeholder for the actual implementation
    // This function should parse the expression and calculate the harmony
    // based on the rules provided in the problem statement.
    return 0; // Placeholder return value
}

int main() {
    int m;
    scanf("%d", &m);
    char expression[400001];
    scanf("%s", expression);
    int len = strlen(expression);

    for (int i = 0; i < m; i++) {
        int a;
        char b;
        scanf("%d %c", &a, &b);
        expression[a - 1] = b;
        ll harmony = calculate_harmony(expression, len);
        printf("%lld\n", harmony);
    }

    return 0;
}