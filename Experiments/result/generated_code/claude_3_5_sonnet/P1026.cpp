#include <stdio.h>
#include <string.h>

#define MAX_LEN 205
#define MAX_WORDS 6
#define MAX_WORD_LEN 20

char str[MAX_LEN];
char words[MAX_WORDS][MAX_WORD_LEN];
int dp[MAX_LEN][41];
int word_count;
int str_len;

int max(int a, int b) {
    return a > b ? a : b;
}

int count_words(int start) {
    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (strncmp(str + start, words[i], strlen(words[i])) == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int p, k, s;
    scanf("%d %d", &p, &k);
    
    for (int i = 0; i < p; i++) {
        char temp[21];
        scanf("%s", temp);
        strcat(str, temp);
    }
    str_len = strlen(str);

    scanf("%d", &s);
    word_count = s;
    for (int i = 0; i < s; i++) {
        scanf("%s", words[i]);
    }

    for (int i = str_len - 1; i >= 0; i--) {
        for (int j = 1; j <= k; j++) {
            if (j == 1) {
                dp[i][j] = count_words(i);
            } else {
                for (int l = i + 1; l < str_len; l++) {
                    dp[i][j] = max(dp[i][j], count_words(i) + dp[l][j-1]);
                }
            }
        }
    }

    printf("%d\n", dp[0][k]);
    return 0;
}