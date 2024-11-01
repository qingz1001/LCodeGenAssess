#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40005
#define MAXQ 100005

int n, q;
char strings[MAXN][MAXN];
int lcp[MAXN][MAXN];

void compute_lcp() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int len1 = strlen(strings[i]);
            int len2 = strlen(strings[j]);
            int min_len = len1 < len2 ? len1 : len2;
            lcp[i][j] = 0;
            for (int k = 0; k < min_len; k++) {
                if (strings[i][k] == strings[j][k]) {
                    lcp[i][j]++;
                } else {
                    break;
                }
            }
        }
    }
}

int compare(const void *a, const void *b) {
    return lcp[*((int *)a)][*((int *)b)] - lcp[*((int *)b)][*((int *)a)];
}

void find_p_star_g(int p_star_g[]) {
    int indices[n];
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    qsort(indices, n, sizeof(int), compare);
    memcpy(p_star_g, indices, n * sizeof(int));
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }

    compute_lcp();

    int p_star_g[n];
    find_p_star_g(p_star_g);

    long long w_p_star_g = 0;
    for (int i = 1; i < n; i++) {
        w_p_star_g += (long long)lcp[p_star_g[i - 1]][p_star_g[i]] * lcp[p_star_g[i - 1]][p_star_g[i]];
    }

    printf("%lld\n", w_p_star_g);

    int satisfied_tasks[MAXQ] = {0};
    int num_satisfied_tasks = 0;

    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;
        int pos_x = -1, pos_y = -1;
        for (int j = 0; j < n; j++) {
            if (p_star_g[j] == x) pos_x = j;
            if (p_star_g[j] == y) pos_y = j;
        }
        if (pos_x + 1 == pos_y) {
            satisfied_tasks[num_satisfied_tasks++] = i + 1;
        }
    }

    printf("%d ", num_satisfied_tasks);
    for (int i = 0; i < num_satisfied_tasks; i++) {
        printf("%d ", satisfied_tasks[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", p_star_g[i] + 1);
    }
    printf("\n");

    return 0;
}