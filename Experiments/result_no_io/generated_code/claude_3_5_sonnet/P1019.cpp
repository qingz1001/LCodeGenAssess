#include <stdio.h>
#include <string.h>

#define MAX_WORDS 20
#define MAX_LENGTH 100

char words[MAX_WORDS][MAX_LENGTH];
int used[MAX_WORDS];
int n;
int max_length = 0;

int overlap(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int max_overlap = 0;
    
    for (int i = 1; i < len1 && i < len2; i++) {
        if (strncmp(s1 + len1 - i, s2, i) == 0) {
            max_overlap = i;
        }
    }
    
    return max_overlap;
}

void dfs(char *current, int length) {
    if (length > max_length) {
        max_length = length;
    }
    
    for (int i = 0; i < n; i++) {
        if (used[i] < 2) {
            int o = overlap(current, words[i]);
            if (o > 0 && o < strlen(words[i])) {
                used[i]++;
                dfs(words[i], length + strlen(words[i]) - o);
                used[i]--;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }
    
    char start;
    scanf(" %c", &start);
    
    for (int i = 0; i < n; i++) {
        if (words[i][0] == start) {
            used[i] = 1;
            dfs(words[i], strlen(words[i]));
            used[i] = 0;
        }
    }
    
    printf("%d\n", max_length);
    
    return 0;
}