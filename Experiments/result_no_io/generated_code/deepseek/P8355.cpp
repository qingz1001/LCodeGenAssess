#include <stdio.h>
#include <string.h>

#define MAXN 1000005

char s[MAXN];

int max_prefix_length(int n) {
    int balance = 0;
    int max_len = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            break;
        }

        if (balance == 0) {
            max_len = i + 1;
        }
    }

    return max_len;
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s);

    printf("%d\n", max_prefix_length(n));

    return 0;
}