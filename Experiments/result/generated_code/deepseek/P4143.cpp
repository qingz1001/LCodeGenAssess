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
    Substring subs[MAXN];
    int sub_count = 0;

    scanf("%s", str);
    N = strlen(str);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }

    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = i; j < N; j++) {
            sum += V[j];
            int len = j - i + 1;
            int rank = 0;
            for (int k = 0; k < N - len + 1; k++) {
                int cmp = strncmp(str + i, str + k, len);
                if (cmp > 0) rank++;
            }
            if (sum == rank + 1) {
                subs[sub_count].l = i + 1;
                subs[sub_count].r = j + 1;
                sub_count++;
            }
        }
    }

    qsort(subs, sub_count, sizeof(Substring), compare);

    printf("%d\n", sub_count);
    for (int i = 0; i < sub_count; i++) {
        printf("%d %d\n", subs[i].l, subs[i].r);
    }

    return 0;
}