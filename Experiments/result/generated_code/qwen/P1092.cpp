#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char a[30], b[30], c[30];
    scanf("%d", &n);
    scanf("%s%s%s", a, b, c);

    int map[26][26];
    memset(map, 0, sizeof(map));

    for (int i = 0; i < n; i++) {
        map[a[i] - 'A'][b[i] - 'A']++;
        map[b[i] - 'A'][a[i] - 'A']++;
        if (i > 0) {
            map[c[i] - 'A'][a[i - 1] - 'A']--;
            map[a[i - 1] - 'A'][c[i] - 'A']--;
        }
    }

    int digits[26];
    memset(digits, 0, sizeof(digits));
    int used[10] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            if (map[j][i] == 1 && !used[digits[j]]) {
                digits[j] = i;
                used[i] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", digits[i]);
    }
    printf("\n");

    return 0;
}