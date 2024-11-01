#include <stdio.h>
#include <string.h>

#define MOD 19930726

int isPalindrome(char *s, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - i - 1]) return 0;
    }
    return 1;
}

int main() {
    int n, K;
    char s[1000001];
    scanf("%d %d", &n, &K);
    scanf("%s", s);

    int count = 0;
    long long product = 1;

    for (int length = 1; length <= n; length++) {
        for (int start = 0; start + length <= n; start++) {
            if ((length & 1) && isPalindrome(&s[start], length)) {
                count++;
                if (count > K) break;
                product = (product * length) % MOD;
            }
        }
        if (count > K) break;
    }

    if (count < K) printf("-1\n");
    else printf("%lld\n", product);

    return 0;
}