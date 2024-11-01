#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_L 500005
#define ALPHABET_SIZE 4

typedef struct {
    char pattern[55];
    int value;
} Mode;

typedef struct {
    int value;
    int index;
} Result;

Mode modes[MAX_N];
char S[MAX_L];
int n, m;

int compare(const void *a, const void *b) {
    return ((Result*)b)->value - ((Result*)a)->value;
}

int kmp(char *text, char *pattern) {
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int next[55] = {0}, j = 0, count = 0;

    for (int i = 1; i < pattern_len; i++) {
        while (j > 0 && pattern[i] != pattern[j]) j = next[j-1];
        if (pattern[i] == pattern[j]) j++;
        next[i] = j;
    }

    j = 0;
    for (int i = 0; i < text_len; i++) {
        while (j > 0 && text[i] != pattern[j]) j = next[j-1];
        if (text[i] == pattern[j]) j++;
        if (j == pattern_len) {
            count++;
            j = next[j-1];
        }
    }

    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s %d", modes[i].pattern, &modes[i].value);
    }

    while (m--) {
        scanf("%s", S);
        int k;
        scanf("%d", &k);

        Result results[MAX_N];
        for (int i = 0; i < n; i++) {
            int count = kmp(S, modes[i].pattern);
            results[i].value = count * modes[i].value;
            results[i].index = i;
        }

        qsort(results, n, sizeof(Result), compare);

        printf("%d\n", results[k-1].value);
    }

    return 0;
}