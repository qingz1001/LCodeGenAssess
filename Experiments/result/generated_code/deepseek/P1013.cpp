#include <stdio.h>
#include <string.h>

#define MAXN 10

char table[MAXN][MAXN][3];
char letters[MAXN];
int values[MAXN];
int n;

int find_index(char c) {
    for (int i = 0; i < n; i++) {
        if (letters[i] == c) return i;
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%s", table[i][j]);
        }
    }

    for (int i = 1; i < n; i++) {
        letters[i-1] = table[0][i][0];
    }

    for (int i = 1; i < n; i++) {
        values[i-1] = -1;
    }

    values[0] = 0; // Assume the first letter is 0

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int len = strlen(table[i][j]);
            if (len == 1) {
                int idx = find_index(table[i][j][0]);
                if (values[idx] == -1) {
                    values[idx] = (values[find_index(table[i][0][0])] + values[find_index(table[0][j][0])]) % (n-1);
                } else {
                    if (values[idx] != (values[find_index(table[i][0][0])] + values[find_index(table[0][j][0])]) % (n-1)) {
                        printf("ERROR!\n");
                        return 0;
                    }
                }
            } else {
                int idx1 = find_index(table[i][j][0]);
                int idx2 = find_index(table[i][j][1]);
                if (values[idx1] == -1) {
                    values[idx1] = (values[find_index(table[i][0][0])] + values[find_index(table[0][j][0])]) / (n-1);
                } else {
                    if (values[idx1] != (values[find_index(table[i][0][0])] + values[find_index(table[0][j][0])]) / (n-1)) {
                        printf("ERROR!\n");
                        return 0;
                    }
                }
                if (values[idx2] == -1) {
                    values[idx2] = (values[find_index(table[i][0][0])] + values[find_index(table[0][j][0])]) % (n-1);
                } else {
                    if (values[idx2] != (values[find_index(table[i][0][0])] + values[find_index(table[0][j][0])]) % (n-1)) {
                        printf("ERROR!\n");
                        return 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n-1; i++) {
        printf("%c=%d ", letters[i], values[i]);
    }
    printf("\n%d\n", n-1);

    return 0;
}