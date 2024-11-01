#include <stdio.h>
#include <string.h>

int n;
char words[21][11];
int count[21] = {0};
int max_length = 0;

void dfs(int index, int length, char start) {
    if (length > max_length) {
        max_length = length;
    }
    for (int i = 0; i < n; i++) {
        if (count[i] < 2) {
            int len1 = strlen(words[index]);
            int len2 = strlen(words[i]);
            int k;
            for (k = 1; k < len1 && k < len2; k++) {
                if (strncmp(words[index] + len1 - k, words[i], k) == 0) {
                    break;
                }
            }
            if (k == len1 || k == len2) {
                count[i]++;
                dfs(i, length + strlen(words[i]) - k, start);
                count[i]--;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }
    char start;
    scanf(" %c", &start);

    for (int i = 0; i < n; i++) {
        if (words[i][0] == start) {
            count[i]++;
            dfs(i, strlen(words[i]), start);
            count[i]--;
        }
    }

    printf("%d\n", max_length);
    return 0;
}