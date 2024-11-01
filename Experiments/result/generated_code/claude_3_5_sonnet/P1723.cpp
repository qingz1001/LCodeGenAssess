#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 10000001

char s[MAX_LENGTH];
int p[MAX_LENGTH * 2];

int min(int a, int b) {
    return a < b ? a : b;
}

int manacher(char* s, int len) {
    int maxLen = 0;
    char t[MAX_LENGTH * 2];
    int tLen = 0;
    
    t[tLen++] = '$';
    t[tLen++] = '#';
    for (int i = 0; i < len; i++) {
        t[tLen++] = s[i];
        t[tLen++] = '#';
    }
    
    int center = 0, right = 0;
    for (int i = 1; i < tLen; i++) {
        if (i < right) {
            p[i] = min(p[2 * center - i], right - i);
        } else {
            p[i] = 1;
        }
        
        while (t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }
        
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        if (p[i] - 1 > maxLen) {
            maxLen = p[i] - 1;
        }
    }
    
    return maxLen;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        int len = strlen(s);
        printf("%d\n", manacher(s, len));
    }
    
    return 0;
}