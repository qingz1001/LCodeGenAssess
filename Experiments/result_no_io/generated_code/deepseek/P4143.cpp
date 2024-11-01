#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct {
    int l, r;
} Substring;

int compare(const void *a, const void *b) {
    Substring *sa = (Substring *)a;
    Substring *sb = (Substring *)b;
    if (sa->l != sb->l) return sa->l - sb->l;
    return sa->r - sb->r;
}

int main() {
    char str[MAXN];
    int V[MAXN];
    int N;
    scanf("%s", str);
    N = strlen(str);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }

    Substring valid_substrings[MAXN];
    int count = 0;

    for (int i = 0; i < N; i++) {
        int importance_sum = 0;
        for (int j = i; j < N; j++) {
            importance_sum += V[j];
            int len = j - i + 1;
            char sub[len + 1];
            strncpy(sub, str + i, len);
            sub[len] = '\0';

            int rank = 1;
            for (int k = 0; k < N; k++) {
                for (int l = k; l < N; l++) {
                    if (k == i && l == j) continue;
                    char other_sub[len + 1];
                    strncpy(other_sub, str + k, len);
                    other_sub[len] = '\0';
                    if (strcmp(sub, other_sub) < 0) rank++;
                }
            }

            if (importance_sum == rank) {
                valid_substrings[count].l = i + 1;
                valid_substrings[count].r = j + 1;
                count++;
            }
        }
    }

    qsort(valid_substrings, count, sizeof(Substring), compare);

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", valid_substrings[i].l, valid_substrings[i].r);
    }

    return 0;
}