#include <stdio.h>
#include <string.h>

#define MAX_WORDS 6
#define MAX_LENGTH 200
#define MAX_LINES 10
#define MAX_WORD_LENGTH 20

int p, k, s;
char lines[MAX_LINES][MAX_WORD_LENGTH];
char words[MAX_WORDS][MAX_WORD_LENGTH];
int wordLengths[MAX_WORDS];
int dp[MAX_LINES][MAX_WORDS][MAX_WORDS];

void preprocess() {
    int i, j;
    for (i = 0; i < s; i++) {
        wordLengths[i] = strlen(words[i]);
    }
}

int check(int line, int start, int end) {
    int i, j;
    for (i = 0; i < s; i++) {
        if (line + 1 == p && start + wordLengths[i] > end) continue;
        if (line + 2 == p && start + wordLengths[i] > 20) continue;
        int match = 1;
        for (j = 0; j < wordLengths[i]; j++) {
            if (lines[line][start + j] != words[i][j]) {
                match = 0;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

int main() {
    int i, j, l, w1, w2;
    scanf("%d%d", &p, &k);
    for (i = 0; i < p; i++) {
        scanf("%s", lines[i]);
    }
    scanf("%d", &s);
    for (i = 0; i < s; i++) {
        scanf("%s", words[i]);
    }
    preprocess();

    for (l = 1; l <= p; l++) {
        for (w1 = 0; w1 < s; w1++) {
            for (w2 = 0; w2 < s; w2++) {
                int max = 0;
                for (i = 0; i < s; i++) {
                    if (i == w1 || i == w2) continue;
                    int start = check(l - 1, 0, 20);
                    if (start != -1) {
                        int end = check(l - 1, 20, 40);
                        if (end != -1) {
                            if (dp[l - 2][start][end] + 1 > max) {
                                max = dp[l - 2][start][end] + 1;
                            }
                        } else {
                            if (dp[l - 2][start][0] + 1 > max) {
                                max = dp[l - 2][start][0] + 1;
                            }
                        }
                    } else {
                        if (dp[l - 2][0][0] + 1 > max) {
                            max = dp[l - 2][0][0] + 1;
                        }
                    }
                }
                dp[l - 1][w1][w2] = max;
            }
        }
    }

    int result = 0;
    for (i = 0; i < s; i++) {
        for (j = 0; j < s; j++) {
            if (dp[p - 1][i][j] > result) {
                result = dp[p - 1][i][j];
            }
        }
    }

    printf("%d\n", result);
    return 0;
}