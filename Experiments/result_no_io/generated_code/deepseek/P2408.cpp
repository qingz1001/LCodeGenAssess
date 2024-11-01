#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 100005

typedef struct {
    int index;
    int rank[2];
} Suffix;

int cmp(const void *a, const void *b) {
    Suffix *sa = (Suffix *)a, *sb = (Suffix *)b;
    return (sa->rank[0] == sb->rank[0]) ? (sa->rank[1] - sb->rank[1]) : (sa->rank[0] - sb->rank[0]);
}

int *buildSuffixArray(char *txt, int n) {
    Suffix suffixes[n];
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
    }
    qsort(suffixes, n, sizeof(Suffix), cmp);
    int ind[n];
    for (int k = 4; k < 2 * n; k *= 2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++) {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
        }

        qsort(suffixes, n, sizeof(Suffix), cmp);
    }

    int *suffixArr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;

    return suffixArr;
}

int64_t countDistinctSubstrings(char *txt, int n) {
    int *suffixArr = buildSuffixArray(txt, n);
    int64_t result = n - suffixArr[0];
    for (int i = 1; i < n; i++) {
        int lcp = 0;
        while (txt[suffixArr[i - 1] + lcp] == txt[suffixArr[i] + lcp]) lcp++;
        result += n - suffixArr[i] - lcp;
    }
    free(suffixArr);
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    char txt[MAXN];
    scanf("%s", txt);
    printf("%lld\n", countDistinctSubstrings(txt, n));
    return 0;
}