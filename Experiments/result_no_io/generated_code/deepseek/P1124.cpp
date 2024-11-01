#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000

typedef struct {
    char str[MAX_N];
    int index;
} StringWithIndex;

int compare(const void *a, const void *b) {
    StringWithIndex *s1 = (StringWithIndex *)a;
    StringWithIndex *s2 = (StringWithIndex *)b;
    int cmp = strcmp(s1->str, s2->str);
    if (cmp == 0) {
        return s1->index - s2->index;
    }
    return cmp;
}

int main() {
    int n;
    char S_prime[MAX_N];
    int p;

    scanf("%d", &n);
    scanf("%s", S_prime);
    scanf("%d", &p);

    StringWithIndex *strings = (StringWithIndex *)malloc(n * sizeof(StringWithIndex));
    for (int i = 0; i < n; i++) {
        strncpy(strings[i].str, S_prime + i, n - i);
        strncpy(strings[i].str + n - i, S_prime, i);
        strings[i].str[n] = '\0';
        strings[i].index = i;
    }

    qsort(strings, n, sizeof(StringWithIndex), compare);

    char S[MAX_N];
    for (int i = 0; i < n; i++) {
        S[i] = strings[i].str[n - 1];
    }
    S[n] = '\0';

    printf("%s\n", S);

    free(strings);
    return 0;
}