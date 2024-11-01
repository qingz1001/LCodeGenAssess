#include <stdio.h>
#include <string.h>

int k, n, m;
int a[100][100], b[100][100];

int main() {
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &n, &m);
        int i, j, t;
        int flag = 0;

        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                scanf("%d", &a[i][j]);

        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                scanf("%d", &b[i][j]);

        // Step 1: Flip rows to match
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (a[i][j] != b[i][j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                for (j = 0; j < m; j++)
                    a[i][j] = 1 - a[i][j];
            flag = 0;
        }

        // Step 2: Check if the two boards are the same after row flipping
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                if (a[i][j] != b[i][j])
                    goto not_same;

        printf("YES\n");
        continue;

    not_same:
        // Step 3: Try to match columns
        for (i = 0; i < m; i++) {
            for (j = i + 1; j < m; j++) {
                flag = 0;
                for (t = 0; t < n; t++) {
                    if (a[t][i] != b[t][j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                    for (t = 0; t < n; t++)
                        a[t][i] = 1 - a[t][i];
                flag = 0;
                for (t = 0; t < n; t++) {
                    if (a[t][i] != b[t][j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                    for (t = 0; t < n; t++)
                        a[t][j] = 1 - a[t][j];
                flag = 0;
                for (t = 0; t < n; t++) {
                    if (a[t][i] != b[t][j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            if (flag)
                break;
        }

        // Step 4: Check if the two boards are the same after column matching
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                if (a[i][j] != b[i][j]) {
                    printf("NO\n");
                    goto next;
                }
        printf("YES\n");

    next:
        ;
    }
    return 0;
}