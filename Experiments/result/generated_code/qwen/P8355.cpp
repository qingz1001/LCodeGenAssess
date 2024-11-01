#include <stdio.h>
#include <string.h>

int max_matching_prefix_length(char *s, int n) {
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
        max_len = i + 1;
    }

    return max_len;
}

int main() {
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);

    printf("%d\n", max_matching_prefix_length(s, n));

    return 0;
}