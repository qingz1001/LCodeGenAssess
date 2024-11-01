#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char str[10001];
    int index;
} StringWithIndex;

int compare(const void *a, const void *b) {
    StringWithIndex *s1 = (StringWithIndex *)a;
    StringWithIndex *s2 = (StringWithIndex *)b;
    return strcmp(s1->str, s2->str);
}

int main() {
    int n;
    char S_prime[10001];
    int p;

    scanf("%d", &n);
    scanf("%s", S_prime);
    scanf("%d", &p);

    StringWithIndex strings[n];
    for (int i = 0; i < n; i++) {
        strncpy(strings[i].str, S_prime + i, n - i);
        strncpy(strings[i].str + n - i, S_prime, i);
        strings[i].str[n] = '\0';
        strings[i].index = i;
    }

    qsort(strings, n, sizeof(StringWithIndex), compare);

    char S[10001];
    for (int i = 0; i < n; i++) {
        S[i] = strings[i].str[n - 1];
    }
    S[n] = '\0';

    printf("%s\n", S);

    return 0;
}