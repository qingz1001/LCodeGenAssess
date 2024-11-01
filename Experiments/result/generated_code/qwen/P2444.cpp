#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000
#define MAX_LEN 10000

int n;
char viruses[MAX_N][MAX_LEN];
int len[MAX_N];

int dfs(int pos) {
    for (int i = 0; i < n; i++) {
        if (strncmp(viruses[i], &viruses[pos][pos], len[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", viruses[i]);
        len[i] = strlen(viruses[i]);
    }

    for (int i = 0; i < n; i++) {
        if (!dfs(i)) {
            printf("NIE\n");
            return 0;
        }
    }

    printf("TAK\n");
    return 0;
}