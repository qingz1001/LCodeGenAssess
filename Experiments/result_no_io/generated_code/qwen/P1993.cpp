#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5005
#define INF 1e9

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *a = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) {
        a[i] = 0;
    }

    int **lower_bound = (int **)malloc((n + 1) * sizeof(int *));
    int **upper_bound = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 1; i <= n; ++i) {
        lower_bound[i] = (int *)malloc((n + 1) * sizeof(int));
        upper_bound[i] = (int *)malloc((n + 1) * sizeof(int));
        for (int j = 1; j <= n; ++j) {
            lower_bound[i][j] = -INF;
            upper_bound[i][j] = INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        int type, a, b, c;
        scanf("%d %d %d", &type, &a, &b);
        if (type == 1) {
            scanf("%d", &c);
            lower_bound[a][b] = c;
        } else if (type == 2) {
            scanf("%d", &c);
            upper_bound[a][b] = c;
        } else {
            lower_bound[a][b] = 0;
            upper_bound[a][b] = 0;
        }
    }

    int valid = 1;
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (lower_bound[i][k] != -INF && lower_bound[k][j] != -INF) {
                    lower_bound[i][j] = lower_bound[i][k] + lower_bound[k][j];
                }
                if (upper_bound[i][k] != INF && upper_bound[k][j] != INF) {
                    upper_bound[i][j] = upper_bound[i][k] + upper_bound[k][j];
                }
                if (lower_bound[j][k] != -INF && lower_bound[k][i] != -INF) {
                    lower_bound[j][i] = lower_bound[j][k] + lower_bound[k][i];
                }
                if (upper_bound[j][k] != INF && upper_bound[k][i] != INF) {
                    upper_bound[j][i] = upper_bound[j][k] + upper_bound[k][i];
                }
                if (lower_bound[i][j] > upper_bound[i][j]) {
                    valid = 0;
                    goto end;
                }
            }
        }
    }

end:
    if (valid) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    free(a);
    for (int i = 1; i <= n; ++i) {
        free(lower_bound[i]);
        free(upper_bound[i]);
    }
    free(lower_bound);
    free(upper_bound);

    return 0;
}