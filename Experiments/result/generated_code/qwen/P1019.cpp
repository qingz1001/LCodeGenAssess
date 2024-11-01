#include <stdio.h>
#include <string.h>

#define MAXN 20
#define MAX_LEN 20

int n;
char words[MAXN][MAX_LEN];
char start_char;
int dp[MAXN];

int can_connect(char *w1, char *w2) {
    int len1 = strlen(w1);
    int len2 = strlen(w2);
    for (int i = 1; i <= len1; i++) {
        if (strcmp(w1 + len1 - i, w2) == 0) return i;
    }
    return 0;
}

void dfs(int index) {
    for (int i = 0; i < n; i++) {
        if (dp[i] > 0 && can_connect(words[index], words[i])) {
            dp[index] = dp[i] + strlen(words[i]) - can_connect(words[index], words[i]);
            dfs(i);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }
    scanf(" %c", &start_char);

    for (int i = 0; i < n; i++) {
        if (words[i][0] == start_char) {
            dp[i] = strlen(words[i]);
            dfs(i);
        }
    }

    int max_len = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) max_len = dp[i];
    }

    printf("%d\n", max_len);

    return 0;
}