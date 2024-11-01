#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char words[n][16];
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        char maxWord[16];
        strcpy(maxWord, words[x-1]); // Initialize maxWord with the first word in the range

        for (int j = x; j <= y; j++) {
            int cmp = strcmp(words[j-1], maxWord);
            if (cmp > 0 || (cmp == 0 && j < y)) {
                strcpy(maxWord, words[j-1]);
            }
        }

        printf("%s\n", maxWord);
    }

    return 0;
}