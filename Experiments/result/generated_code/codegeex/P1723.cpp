#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char s[10000000];
        scanf("%s", s);
        int len = strlen(s);
        int maxlen = 1;
        for (int i = 0; i < len; i++) {
            int l = i, r = i;
            while (l >= 0 && r < len && s[l] == s[r]) {
                if (r - l + 1 > maxlen) {
                    maxlen = r - l + 1;
                }
                l--;
                r++;
            }
            l = i;
            r = i + 1;
            while (l >= 0 && r < len && s[l] == s[r]) {
                if (r - l + 1 > maxlen) {
                    maxlen = r - l + 1;
                }
                l--;
                r++;
            }
        }
        printf("%d\n", maxlen);
    }
    return 0;
}