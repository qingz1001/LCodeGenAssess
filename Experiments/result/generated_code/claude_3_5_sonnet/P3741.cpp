#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 101

int countVK(char* s, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'V' && s[i+1] == 'K') {
            count++;
        }
    }
    return count;
}

int maxVK(char* s, int n) {
    int original = countVK(s, n);
    int max = original;

    for (int i = 0; i < n; i++) {
        char original_char = s[i];
        
        if (s[i] == 'V') {
            s[i] = 'K';
        } else {
            s[i] = 'V';
        }

        int new_count = countVK(s, n);
        if (new_count > max) {
            max = new_count;
        }

        s[i] = original_char;
    }

    return max;
}

int main() {
    int n;
    char s[MAX_LENGTH];

    scanf("%d", &n);
    scanf("%s", s);

    int result = maxVK(s, n);
    printf("%d\n", result);

    return 0;
}