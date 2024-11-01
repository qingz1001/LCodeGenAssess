#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 400005
#define MOD 998244353

typedef long long ll;

int m, len;
char s[MAX_LEN];

int main() {
    scanf("%d", &m);
    scanf("%s", s);
    len = strlen(s);

    while (m--) {
        int pos;
        char ch;
        scanf("%d %c", &pos, &ch);

        // Update the expression at the specified position
        s[pos - 1] = ch;

        // Calculate the harmonic value of the expression
        ll harmonic_value = 0;

        // Implement the logic to calculate the harmonic value
        // ...

        // Output the result
        printf("%lld\n", harmonic_value % MOD);
    }

    return 0;
}