#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m, c, q;
    scanf("%d %d %d %d", &n, &m, &c, &q);

    char **templates = (char **)malloc(q * sizeof(char *));
    for (int i = 0; i < q; i++) {
        templates[i] = (char *)malloc(c * sizeof(char));
    }

    for (int i = 0; i < q; i++) {
        scanf("%s", templates[i]);
    }

    for (int i = 0; i < q; i++) {
        long long count = 0;
        for (int j = 0; j <= n - 2; j++) {
            for (int k = 0; k <= m - c; k++) {
                int match = 1;
                for (int l = 0; l < c; l++) {
                    if (templates[i][l] != 'X' && templates[i][l] != board[j][k + l]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    count++;
                }
            }
        }
        printf("%lld\n", count);
    }

    for (int i = 0; i < q; i++) {
        free(templates[i]);
    }
    free(templates);

    return 0;
}