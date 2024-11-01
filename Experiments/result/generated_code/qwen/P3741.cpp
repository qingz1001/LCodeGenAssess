#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);

    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'V' && s[i + 1] == 'K') {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}