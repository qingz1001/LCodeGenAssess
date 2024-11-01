#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10

int main() {
    int n;
    scanf("%d", &n);
    char table[MAXN][MAXN][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%s", table[i][j]);
        }
    }

    int num_map[26];
    memset(num_map, -1, sizeof(num_map));
    int base = -1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (num_map[table[i-1][j-1][0] - 'A'] == -1) {
                num_map[table[i-1][j-1][0] - 'A'] = i + j - 2;
            } else if (num_map[table[i-1][j-1][0] - 'A'] != i + j - 2) {
                printf("ERROR!\n");
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int sum = num_map[table[i-1][j-1][0] - 'A'];
            if (base == -1) {
                base = sum;
            } else if (sum % base != 0) {
                printf("ERROR!\n");
                return 0;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (num_map[i] != -1) {
            printf("%c=%d ", i + 'A', num_map[i]);
        }
    }
    printf("\n%d\n", base);

    return 0;
}