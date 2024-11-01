#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char a[101], b[101], c[101];
    scanf("%s %s %s", a, b, c);

    int digits[26];
    memset(digits, -1, sizeof(digits));
    int used[10] = {0};

    for (int i = 0; i < n; i++) {
        if (digits[a[i] - 'A'] == -1) {
            for (int j = 0; j < 10; j++) {
                if (!used[j]) {
                    digits[a[i] - 'A'] = j;
                    used[j] = 1;
                    break;
                }
            }
        }

        if (digits[b[i] - 'A'] == -1) {
            for (int j = 0; j < 10; j++) {
                if (!used[j]) {
                    digits[b[i] - 'A'] = j;
                    used[j] = 1;
                    break;
                }
            }
        }

        if (digits[c[i] - 'A'] == -1) {
            for (int j = 0; j < 10; j++) {
                if (!used[j]) {
                    digits[c[i] - 'A'] = j;
                    used[j] = 1;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", digits[a[i] - 'A']);
    }
    return 0;
}