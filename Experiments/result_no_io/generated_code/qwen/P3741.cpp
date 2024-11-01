#include <stdio.h>
#include <string.h>

int max.VK(char *s, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'V' && s[i + 1] == 'K') {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);

    int original_count = max.VK(s, n);
    int best_count = original_count;

    for (int i = 0; i < n; i++) {
        for (char new_char : "VK") {
            if (new_char != s[i]) {
                s[i] = new_char;
                int new_count = max.VK(s, n);
                if (new_count > best_count) {
                    best_count = new_count;
                }
                s[i] = original_char;
            }
        }
    }

    printf("%d\n", best_count);
    return 0;
}