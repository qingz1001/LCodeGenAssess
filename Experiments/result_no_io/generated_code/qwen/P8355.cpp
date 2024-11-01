#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);

    int balance = 0, max_prefix_length = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            break;
        }

        max_prefix_length = i + 1;
    }

    printf("%d\n", max_prefix_length);

    return 0;
}