#include <stdio.h>
#include <string.h>

#define MAX_LEN 200
#define MAX_WORDS 6
#define MAX_WORD_LEN 20

int p, k, s;
char input[MAX_LEN + 1];
char words[MAX_WORDS][MAX_WORD_LEN + 1];
int dp[MAX_LEN + 1][MAX_LEN + 1][k + 1];
int wordLen[MAX_WORDS];
int wordCount[MAX_LEN + 1][MAX_LEN + 1];

void preprocess() {
    scanf("%d%d", &p, &k);
    for (int i = 0; i < p; i++) {
        scanf("%s", input + i * 20);
    }
    scanf("%d", &s);
    for (int i = 0; i < s; i++) {
        scanf("%s", words[i]);
        wordLen[i] = strlen(words[i]);
    }
    
    // 计算每个子串中包含的单词个数
    for (int i = 0; i < p; i++) {
        for (int j = i * 20; j < (i + 1) * 20; j++) {
            for (int l = j; l < (i + 1) * 20; l++) {
                for (int m = 0; m < s; m++) {
                    if (strncmp(input + j, words[m], wordLen[m]) == 0) {
                        wordCount[j][l]++;
                    }
                }
            }
        }
    }
}

int solve() {
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < p; i++) {
        for (int j = i * 20; j < (i + 1) * 20; j++) {
            for (int l = j; l < (i + 1) * 20; l++) {
                for (int m = 1; m <= k; m++) {
                    for (int n = i * 20; n < j; n++) {
                        dp[j][l][m] = fmax(dp[j][l][m], dp[n][j][m - 1] + wordCount[j][l]);
                    }
                }
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < p; i++) {
        for (int j = i * 20; j < (i + 1) * 20; j++) {
            result = fmax(result, dp[j][(i + 1) * 20 - 1][k]);
        }
    }
    return result;
}

int main() {
    preprocess();
    printf("%d\n", solve());
    return 0;
}