#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);

    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int found = 0;
            for (int k = 0; k <= j - i; k++) {
                if (found) break;
                for (int l = 0; l <= j - i; l++) {
                    if (k != l && s[i + k] == s[j - i + l]) {
                        found = 1;
                        break;
                    }
                }
            }
            if (!found) count++;
        }
    }

    printf("%lld\n", count);
    return 0;
}