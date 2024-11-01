#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005
#define MAXL 500005

int n, m;
char s[MAXN][MAXL];
int v[MAXN];
char S[MAXM][MAXL];
int k[MAXM];

void read_input() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s %d", s[i], &v[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%s %d", S[i], &k[i]);
    }
}

int count_occurrences(const char *str, const char *pattern) {
    int count = 0;
    size_t pos = 0;
    while ((pos = strstr(str, pattern)) != NULL) {
        count++;
        str = pos + strlen(pattern);
    }
    return count;
}

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    read_input();

    for (int i = 0; i < m; ++i) {
        int max_beauty = 0;
        for (int j = 0; j < n; ++j) {
            int cnt = count_occurrences(S[i], s[j]);
            int beauty = cnt * v[j];
            if (beauty > max_beauty) {
                max_beauty = beauty;
            }
        }
        printf("%d\n", max_beauty);
    }

    return 0;
}