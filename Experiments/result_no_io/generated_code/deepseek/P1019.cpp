#include <stdio.h>
#include <string.h>

#define MAXN 21
#define MAXL 21

int n;
char words[MAXN][MAXL];
int used[MAXN];
int max_length = 0;

int overlap(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    for (int i = 1; i < len_a && i < len_b; i++) {
        if (strncmp(a + len_a - i, b, i) == 0) {
            return i;
        }
    }
    return 0;
}

void dfs(char *start, int current_length) {
    if (current_length > max_length) {
        max_length = current_length;
    }
    for (int i = 0; i < n; i++) {
        if (used[i] < 2) {
            int o = overlap(start, words[i]);
            if (o > 0) {
                used[i]++;
                dfs(words[i], current_length + strlen(words[i]) - o);
                used[i]--;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }
    char start_char;
    scanf(" %c", &start_char);

    for (int i = 0; i < n; i++) {
        if (words[i][0] == start_char) {
            used[i]++;
            dfs(words[i], strlen(words[i]));
            used[i]--;
        }
    }

    printf("%d\n", max_length);
    return 0;
}