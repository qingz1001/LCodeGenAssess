#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-4

typedef struct {
    double p1;
    double p2[2];
} Game;

Game games[200001];
int known[200001];

double expect(int n) {
    double r_win = 0, b_win = 0;
    for (int i = 1; i <= n; i++) {
        if (known[i]) {
            if (games[i].p1 == 1) {
                r_win += 1;
            } else if (games[i].p1 == 0) {
                b_win += 1;
            } else {
                r_win += games[i].p1 * (1 - b_win);
                b_win += (1 - games[i].p1) * (1 - r_win);
            }
        }
    }
    return r_win;
}

int main() {
    int n, m;
    char type[2];
    scanf("%d %d %s", &n, &m, type);

    for (int i = 1; i <= n; i++) {
        scanf("%lf", &games[i].p1);
    }

    for (int i = 2; i <= n; i++) {
        scanf("%lf %lf", &games[i].p2[0], &games[i].p2[1]);
    }

    for (int i = 1; i <= m; i++) {
        int op, idx, val;
        scanf("%d %d", &op, &idx);
        if (op == 1) {
            scanf("%d", &val);
            known[idx] = 1;
            if (val == 0) {
                games[idx].p1 = 0;
            } else {
                games[idx].p1 = 1;
            }
        } else {
            known[idx] = 0;
        }
        printf("%.6f\n", expect(n));
    }

    return 0;
}