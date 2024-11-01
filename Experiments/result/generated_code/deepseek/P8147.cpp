#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000
#define MAX_L 500000

typedef struct {
    char *s;
    int v;
} Mode;

typedef struct {
    char *S;
    int k;
} Query;

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int countOccurrences(const char *str, const char *substr) {
    int count = 0;
    const char *tmp = str;
    while ((tmp = strstr(tmp, substr))) {
        count++;
        tmp++;
    }
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Mode modes[MAX_N];
    Query queries[MAX_N];

    for (int i = 0; i < n; i++) {
        modes[i].s = (char *)malloc(MAX_L + 1);
        scanf("%s %d", modes[i].s, &modes[i].v);
    }

    for (int i = 0; i < m; i++) {
        queries[i].S = (char *)malloc(MAX_L + 1);
        scanf("%s %d", queries[i].S, &queries[i].k);
    }

    for (int i = 0; i < m; i++) {
        int values[MAX_N];
        for (int j = 0; j < n; j++) {
            int cnt = countOccurrences(queries[i].S, modes[j].s);
            values[j] = cnt * modes[j].v;
        }
        qsort(values, n, sizeof(int), compare);
        printf("%d\n", values[queries[i].k - 1]);
    }

    for (int i = 0; i < n; i++) {
        free(modes[i].s);
    }

    for (int i = 0; i < m; i++) {
        free(queries[i].S);
    }

    return 0;
}