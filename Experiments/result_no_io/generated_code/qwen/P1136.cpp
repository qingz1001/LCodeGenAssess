#include <stdio.h>
#include <string.h>

int maxJZ(char *s, int n, int k) {
    int j = 0;
    for (int i = 0; i < n - 1 && k > 0; i++) {
        if (s[i] == 'j' && s[i + 1] == 'z') {
            j++;
            i++; // Skip the next character as it's already in the correct position
            k--;
        }
    }
    return j;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    char s[501];
    scanf("%s", s);
    printf("%d\n", maxJZ(s, n, k));
    return 0;
}