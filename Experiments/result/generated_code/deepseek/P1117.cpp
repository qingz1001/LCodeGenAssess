#include <stdio.h>
#include <string.h>

#define MAXN 30005

int count_aabb(char *s, int n) {
    int count = 0;
    for (int len = 1; len <= n / 2; len++) {
        for (int i = 0; i + 2 * len <= n; i++) {
            if (strncmp(s + i, s + i + len, len) == 0 && strncmp(s + i + len, s + i + 2 * len, len) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char s[MAXN];
        scanf("%s", s);
        int n = strlen(s);
        int result = count_aabb(s, n);
        printf("%d\n", result);
    }
    return 0;
}