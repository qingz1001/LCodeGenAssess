#include <stdio.h>
#include <string.h>

#define MAX_LEN 200
#define MAX_WORDS 6
#define MAX_PARTS 40

int p, k, s;
char str[MAX_LEN + 1];
char words[MAX_WORDS][MAX_LEN + 1];
int dp[MAX_LEN + 1][MAX_PARTS + 1];

int is_word_in_str(int start, int end, char *word) {
    int word_len = strlen(word);
    if (end - start + 1 < word_len) return 0;
    for (int i = 0; i < word_len; i++) {
        if (str[start + i] != word[i]) return 0;
    }
    return 1;
}

int count_words(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        for (int j = 0; j < s; j++) {
            if (is_word_in_str(i, end, words[j])) {
                count++;
                break;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &p, &k);
    str[0] = '\0';
    for (int i = 0; i < p; i++) {
        char temp[21];
        scanf("%s", temp);
        strcat(str, temp);
    }
    scanf("%d", &s);
    for (int i = 0; i < s; i++) {
        scanf("%s", words[i]);
    }

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = 0;
            for (int m = 0; m < i; m++) {
                int words_count = count_words(m + 1, i);
                if (dp[m][j - 1] + words_count > dp[i][j]) {
                    dp[i][j] = dp[m][j - 1] + words_count;
                }
            }
        }
    }

    printf("%d\n", dp[len - 1][k]);
    return 0;
}