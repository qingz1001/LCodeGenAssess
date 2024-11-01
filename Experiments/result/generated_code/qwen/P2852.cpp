#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20005
#define MAX_K 20005

int n, k;
int milk[MAX_N];

typedef struct {
    int start;
    int len;
} Pattern;

int compare(const void *a, const void *b) {
    return ((Pattern *)a)->len - ((Pattern *)b)->len;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &milk[i]);
    }

    int max_len = 0;
    for (int len = 1; len <= n / k; len++) {
        if (len > max_len) {
            Pattern patterns[n];
            int count = 0;

            for (int start = 0; start + len <= n; start++) {
                int found = 0;
                for (int j = 0; j < count; j++) {
                    if (patterns[j].start == start && patterns[j].len == len) {
                        patterns[j].len++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    patterns[count++] = (Pattern){start, len};
                }
            }

            qsort(patterns, count, sizeof(Pattern), compare);

            for (int i = 0; i < count; i++) {
                if (patterns[i].len >= k) {
                    max_len = patterns[i].len;
                    break;
                }
            }
        }
    }

    printf("%d\n", max_len);
    return 0;
}