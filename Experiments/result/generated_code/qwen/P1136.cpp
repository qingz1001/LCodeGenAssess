#include <stdio.h>
#include <string.h>

int maxJZSubstrings(char *s, int n, int k) {
    int count = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (s[i] == 'j' && s[i + 1] == 'z') {
            count++;
            i++; // Skip the next character as it is part of a jz pair
        }
    }
    return count;
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    char s[n + 1];
    scanf("%s", s);

    while (k > 0) {
        int found = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (s[i] == 'j' && s[i + 1] != 'z') {
                swap(&s[i], &s[i + 1]);
                found = 1;
                break;
            } else if (s[i] != 'j' && s[i + 1] == 'z') {
                swap(&s[i], &s[i + 1]);
                found = 1;
                break;
            }
        }
        if (!found) break;
        k--;
    }

    printf("%d\n", maxJZSubstrings(s, n, 0));
    return 0;
}