#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 20
#define MAX_LEN 20

typedef struct {
    char str[MAX_LEN + 1];
    int len;
} Code;

Code codes[MAX_N];
int n;

int compare(const void *a, const void *b) {
    Code *codeA = (Code *)a;
    Code *codeB = (Code *)b;
    return strcmp(codeA->str, codeB->str);
}

int canForm(char *target, int len) {
    int dp[len + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= len; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= codes[j].len && strncmp(target + i - codes[j].len, codes[j].str, codes[j].len) == 0) {
                dp[i] += dp[i - codes[j].len];
                if (dp[i] > 1) return 1;
            }
        }
    }
    return dp[len] > 1;
}

void findShortestCode() {
    char target[MAX_N * MAX_LEN + 1];
    int minLen = 0;
    int found = 0;

    while (!found) {
        minLen++;
        for (int i = 0; i < n; i++) {
            if (codes[i].len == minLen) {
                if (canForm(codes[i].str, minLen)) {
                    printf("%d\n%s\n", minLen, codes[i].str);
                    found = 1;
                    break;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", codes[i].str);
        codes[i].len = strlen(codes[i].str);
    }

    qsort(codes, n, sizeof(Code), compare);

    findShortestCode();

    return 0;
}