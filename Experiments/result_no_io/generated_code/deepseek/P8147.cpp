#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXL 500005

typedef struct {
    char str[10];
    int val;
} Pattern;

Pattern patterns[MAXN];

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int countOccurrences(char *str, char *sub) {
    int count = 0, len = strlen(sub);
    while ((str = strstr(str, sub)) != NULL) {
        count++;
        str += len;
    }
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%s %d", patterns[i].str, &patterns[i].val);
    }

    for (int i = 0; i < m; i++) {
        char S[MAXL];
        int k;
        scanf("%s %d", S, &k);

        int values[MAXN];
        for (int j = 0; j < n; j++) {
            int cnt = countOccurrences(S, patterns[j].str);
            values[j] = cnt * patterns[j].val;
        }

        qsort(values, n, sizeof(int), compare);

        printf("%d\n", values[k - 1]);
    }

    return 0;
}