#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25
#define MAX_M 250

int compare(const void *a, const void *b) {
    int **x = (int **)a;
    int **y = (int **)b;
    if ((*x)[1] != (*y)[1]) return (*x)[1] - (*y)[1];
    return (*x)[0] - (*y)[0];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int ps[MAX_M + 1][MAX_M + 1];
    int count = 0;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            ps[count][0] = i * i + j * j;
            ps[count][1] = i;
            count++;
        }
    }

    qsort(ps, count, sizeof(int *) * 2, compare);

    for (int i = 0; i <= count - n; i++) {
        int diff = ps[i + 1][0] - ps[i][0];
        int valid = 1;
        for (int j = 2; j < n; j++) {
            if (ps[i + j][0] - ps[i + j - 1][0] != diff) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            for (int j = i; j < i + n; j++) {
                printf("%d %d\n", ps[j][0], ps[j][1]);
            }
            return 0;
        }
    }

    printf("NONE\n");
    return 0;
}