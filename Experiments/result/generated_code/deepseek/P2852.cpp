#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20000
#define MAXQ 1000000

typedef struct {
    int index;
    int rank[2];
} Suffix;

int cmp(const void *a, const void *b) {
    Suffix *sa = (Suffix *)a;
    Suffix *sb = (Suffix *)b;
    return (sa->rank[0] == sb->rank[0]) ? (sa->rank[1] - sb->rank[1]) : (sa->rank[0] - sb->rank[0]);
}

int *buildSuffixArray(int *arr, int n) {
    Suffix *suffixes = (Suffix *)malloc(n * sizeof(Suffix));
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = arr[i];
        suffixes[i].rank[1] = (i + 1 < n) ? arr[i + 1] : -1;
    }

    qsort(suffixes, n, sizeof(Suffix), cmp);

    int *ind = (int *)malloc(n * sizeof(int));
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

    free(suffixes);
    free(ind);
    return suffixArr;
}

int *kasai(int *arr, int *suffixArr, int n) {
    int *lcp = (int *)malloc(n * sizeof(int));
    int *invSuff = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        invSuff[suffixArr[i]] = i;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (invSuff[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suffixArr[invSuff[i] + 1];
        while (i + k < n && j + k < n && arr[i + k] == arr[j + k])
            k++;

        lcp[invSuff[i]] = k;
        if (k > 0)
            k--;
    }

    free(invSuff);
    return lcp;
}

int findLongestPattern(int *arr, int n, int k) {
    int *suffixArr = buildSuffixArray(arr, n);
    int *lcp = kasai(arr, suffixArr, n);

    int maxLen = 0;
    for (int i = 0; i <= n - k; i++) {
        int len = lcp[i];
        for (int j = i + 1; j < i + k - 1; j++) {
            if (lcp[j] < len)
                len = lcp[j];
        }
        if (len > maxLen)
            maxLen = len;
    }

    free(suffixArr);
    free(lcp);
    return maxLen;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = findLongestPattern(arr, n, k);
    printf("%d\n", result);

    free(arr);
    return 0;
}