#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 101

int countVK(char *s) {
    int count = 0;
    for (int i = 0; s[i] && s[i+1]; i++) {
        if (s[i] == 'V' && s[i+1] == 'K') {
            count++;
            i++;
        }
    }
    return count;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    char s[MAX_LENGTH];
    
    scanf("%d", &n);
    scanf("%s", s);
    
    int original_count = countVK(s);
    int max_count = original_count;
    
    for (int i = 0; i < n; i++) {
        char original = s[i];
        
        // Try changing to 'V'
        if (s[i] != 'V') {
            s[i] = 'V';
            max_count = max(max_count, countVK(s));
        }
        
        // Try changing to 'K'
        if (original != 'K') {
            s[i] = 'K';
            max_count = max(max_count, countVK(s));
        }
        
        // Restore original character
        s[i] = original;
    }
    
    printf("%d\n", max_count);
    
    return 0;
}