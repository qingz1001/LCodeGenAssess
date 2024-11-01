#include <stdio.h>
#include <string.h>

int countVK(char *s) {
    int count = 0;
    for (int i = 0; s[i] != '\0' && s[i + 1] != '\0'; i++) {
        if (s[i] == 'V' && s[i + 1] == 'K') {
            count++;
        }
    }
    return count;
}

int maxVK(char *s) {
    int n = strlen(s);
    int maxCount = countVK(s);

    for (int i = 0; i < n; i++) {
        char original = s[i];
        if (s[i] == 'V') {
            s[i] = 'K';
        } else if (s[i] == 'K') {
            s[i] = 'V';
        }

        int newCount = countVK(s);
        if (newCount > maxCount) {
            maxCount = newCount;
        }

        s[i] = original; // restore the original character
    }

    return maxCount;
}

int main() {
    int n;
    char s[101];

    scanf("%d", &n);
    scanf("%s", s);

    int result = maxVK(s);
    printf("%d\n", result);

    return 0;
}