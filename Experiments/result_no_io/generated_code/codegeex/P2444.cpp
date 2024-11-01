#include <stdio.h>
#include <string.h>

#define MAXN 2000
#define MAXLEN 30000

int n;
char viruses[MAXN][MAXLEN + 1];
int trie[MAXLEN + 1][2];
int end[MAXLEN + 1];
int tot;

void insert(char *s) {
    int len = strlen(s);
    int p = 0;
    for (int i = 0; i < len; i++) {
        int c = s[i] - '0';
        if (!trie[p][c]) {
            trie[p][c] = ++tot;
        }
        p = trie[p][c];
    }
    end[p] = 1;
}

int search(char *s) {
    int len = strlen(s);
    int p = 0;
    for (int i = 0; i < len; i++) {
        int c = s[i] - '0';
        if (!trie[p][c] || end[trie[p][c]]) {
            return 0;
        }
        p = trie[p][c];
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", viruses[i]);
        insert(viruses[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                char s[MAXLEN * 2 + 1];
                strcpy(s, viruses[i]);
                strcat(s, viruses[j]);
                if (search(s)) {
                    printf("NIE\n");
                    return 0;
                }
            }
        }
    }
    printf("TAK\n");
    return 0;
}