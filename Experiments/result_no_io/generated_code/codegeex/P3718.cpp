#include <stdio.h>
#include <string.h>

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    char s[100005];
    scanf("%s", s);

    int max = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == s[i + 1]) {
            cnt++;
        } else {
            if (cnt > max) {
                max = cnt;
            }
            cnt = 0;
        }
    }

    if (max <= k) {
        printf("1");
    } else {
        printf("%d", max - k + 1);
    }

    return 0;
}