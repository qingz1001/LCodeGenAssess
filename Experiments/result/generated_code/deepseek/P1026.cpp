#include <stdio.h>
#include <string.h>

#define MAX_LEN 200
#define MAX_WORDS 6

int p, k, s;
char str[MAX_LEN + 1];
char words[MAX_WORDS][MAX_LEN + 1];
int dp[MAX_LEN + 1][MAX_LEN + 1];

int is_word_in_str(int start, char *word) {
    int len = strlen(word);
    if (start + len > strlen(str)) return 0;
    for (int i = 0; i < len; i++) {
        if (str[start + i] != word[i]) return 0;
    }
    return 1;
}

int count_words(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        for (int j = 0; j < s; j++) {
            if (is_word_in_str(i, words[j])) {
                count++;
                break;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &p, &k);
    int len = 0;
    for (int i = 0; i < p; i++) {
        char line[21];
        scanf("%s", line);
        strcpy(str + len, line);
        len += 20;
    }
    scanf("%d", &s);
    for (int i = 0; i < s; i++) {
        scanf("%s", words[i]);
    }

    for (int i = 0; i < len; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = 0;
            for (int m = i; m >= 0; m--) {
                int word_count = count_words(m, i);
                if (m == 0) {
                    dp[i][j] = word_count;
                } else {
                    dp[i][j] = dp[i][j] > dp[m - 1][j - 1] + word_count ? dp[i][j] : dp[m - 1][j - 1] + word_count;
                }
            }
        }
    }

    printf("%d\n", dp[len - 1][k]);
    return 0;
}