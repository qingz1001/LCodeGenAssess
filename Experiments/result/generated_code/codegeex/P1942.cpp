#include <stdio.h>
#include <string.h>

int n;
char str[1001];

void solve() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == '1') sum += i + 1;
    }
    if (sum % (n + 1) == 0) {
        printf("%s\n", str);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (str[i] == '0') {
            str[i] = '1';
            sum += i + 1;
            if (sum % (n + 1) == 0) {
                printf("%s\n", str);
                return;
            }
            str[i] = '0';
        }
    }

    for (int i = 0; i <= n; i++) {
        str[i] = '0';
        sum += i + 1;
        if (sum % (n + 1) == 0) {
            printf("%s\n", str);
            return;
        }
        str[i] = '1';
        sum += i + 1;
        if (sum % (n + 1) == 0) {
            printf("%s\n", str);
            return;
        }
        str[i] = '\0';
    }

    for (int i = 0; i < n; i++) {
        str[i] = '1';
        sum -= i + 1;
        if (sum % (n + 1) == 0) {
            printf("%s\n", str);
            return;
        }
        str[i] = '0';
        sum -= i + 1;
        if (sum % (n + 1) == 0) {
            printf("%s\n", str);
            return;
        }
        str[i] = '\0';
    }

    printf("-1\n");
}

int main() {
    scanf("%d", &n);
    while (scanf("%s", str) != EOF) {
        solve();
    }
    return 0;
}