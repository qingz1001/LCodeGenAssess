#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef long long ll;

int n;
char s[MAXN];

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);

    char *substrings[MAXN * 50];
    int count = 0;

    for (int len = 1; len <= n; len++) {
        for (int start = 0; start <= n - len; start++) {
            substrings[count] = (char *)malloc((len + 1) * sizeof(char));
            strncpy(substrings[count], s + start, len);
            substrings[count][len] = '\0';
            count++;
        }
    }

    qsort(substrings, count, sizeof(char *), cmp);

    ll unique_count = 1;
    for (int i = 1; i < count; i++) {
        if (strcmp(substrings[i], substrings[i - 1]) != 0) {
            unique_count++;
        }
        free(substrings[i]);
    }
    free(substrings[0]);

    printf("%lld\n", unique_count);

    return 0;
}