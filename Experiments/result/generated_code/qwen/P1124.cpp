#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10005

typedef struct {
    char str[MAXN];
    int index;
} StringInfo;

int compare(const void *a, const void *b) {
    StringInfo *strA = (StringInfo *)a;
    StringInfo *strB = (StringInfo *)b;
    if (strA->str[0] == strB->str[0]) {
        return strA->index - strB->index;
    }
    return strA->str[0] - strB->str[0];
}

int main() {
    int n, p;
    char S_prime[MAXN];
    scanf("%d %s %d", &n, S_prime, &p);

    StringInfo strings[n];
    for (int i = 0; i < n; ++i) {
        strcpy(strings[i].str, S_prime);
        strings[i].index = i;
        for (int j = 0; j < n - 1; ++j) {
            char temp = strings[i].str[j];
            strings[i].str[j] = strings[i].str[j + 1];
            strings[i].str[j + 1] = temp;
        }
    }

    qsort(strings, n, sizeof(StringInfo), compare);

    char S[MAXN];
    for (int i = 0; i < n; ++i) {
        S[i] = strings[i].str[n - 1];
    }
    S[n] = '\0';

    printf("%s\n", S);

    return 0;
}