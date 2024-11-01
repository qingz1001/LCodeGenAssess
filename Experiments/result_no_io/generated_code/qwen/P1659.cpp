#include <stdio.h>
#include <string.h>

#define MOD 19930726

int isPalindrome(char *s, int len) {
    for (int i = 0; i < len / 2; ++i) {
        if (s[i] != s[len - i - 1]) return 0;
    }
    return 1;
}

int main() {
    int n, K;
    scanf("%d %d", &n, &K);
    char s[n + 1];
    scanf("%s", s);

    int count = 0;
    long long product = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 1; i + j <= n; ++j) {
            if ((j + 1) % 2 == 1 && isPalindrome(s + i, j)) {
                product = (product * j) % MOD;
                ++count;
                if (count >= K) break;
            }
        }
        if (count >= K) break;
    }

    if (count < K) {
        printf("-1\n");
    } else {
        printf("%lld\n", product);
    }

    return 0;
}