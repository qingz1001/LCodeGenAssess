#include <stdio.h>
#include <string.h>

#define MAXN 1000005

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    char s[MAXN];
    scanf("%d", &n);
    scanf("%s", s);

    int balance = 0;
    int max_prefix = 0;
    int max_balance = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            balance = 0;
        }

        if (balance == 0) {
            max_prefix = i + 1;
        }

        max_balance = max(max_balance, balance);
    }

    printf("%d\n", max_prefix);

    return 0;
}