#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10001

typedef struct {
    char c;
    int index;
} CharIndex;

int compare(const void *a, const void *b) {
    CharIndex *ca = (CharIndex *)a;
    CharIndex *cb = (CharIndex *)b;
    if (ca->c != cb->c) {
        return ca->c - cb->c;
    }
    return ca->index - cb->index;
}

int main() {
    int n, p;
    char s_prime[MAX_LEN];
    CharIndex char_indices[MAX_LEN];
    int next[MAX_LEN];

    scanf("%d", &n);
    scanf("%s", s_prime);
    scanf("%d", &p);

    for (int i = 0; i < n; i++) {
        char_indices[i].c = s_prime[i];
        char_indices[i].index = i;
    }

    qsort(char_indices, n, sizeof(CharIndex), compare);

    for (int i = 0; i < n; i++) {
        next[char_indices[i].index] = i;
    }

    char s[MAX_LEN];
    int current = p - 1;
    for (int i = 0; i < n; i++) {
        s[i] = s_prime[current];
        current = next[current];
    }
    s[n] = '\0';

    printf("%s\n", s);

    return 0;
}