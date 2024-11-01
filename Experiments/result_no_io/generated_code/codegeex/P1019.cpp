#include <stdio.h>
#include <string.h>

int n, max = 0;
char word[25][20];
int cnt[25];
char start;

int common(char *s1, char *s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int i, j;
    for (i = 1; i <= len1; i++) {
        for (j = 1; j <= len2; j++) {
            if (strncmp(s1 + i, s2, j) == 0) {
                return j;
            }
        }
    }
    return 0;
}

void dfs(int step, int last, int len) {
    if (step > max) {
        max = step;
    }
    for (int i = 0; i < n; i++) {
        if (cnt[i] < 2) {
            int c = common(word[last], word[i]);
            if (c > 0) {
                cnt[i]++;
                dfs(step + strlen(word[i]) - c, i, len + strlen(word[i]) - c);
                cnt[i]--;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", word[i]);
    }
    scanf(" %c", &start);
    for (int i = 0; i < n; i++) {
        if (word[i][0] == start) {
            cnt[i]++;
            dfs(1, i, strlen(word[i]));
            cnt[i]--;
        }
    }
    printf("%d\n", max);
    return 0;
}