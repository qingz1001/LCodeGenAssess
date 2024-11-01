#include <stdio.h>
#include <string.h>

#define MOD 998244353

typedef long long ll;

ll calculate_harmony(char *expr, int len) {
    // Placeholder function to calculate harmony
    // This function should be implemented based on the problem requirements
    return 0;
}

int main() {
    int m;
    scanf("%d", &m);
    char expr[400001];
    scanf("%s", expr);
    int len = strlen(expr);

    for (int i = 0; i < m; i++) {
        int a;
        char b;
        scanf("%d %c", &a, &b);
        expr[a] = b;
        ll harmony = calculate_harmony(expr, len);
        printf("%lld\n", harmony % MOD);
    }

    return 0;
}