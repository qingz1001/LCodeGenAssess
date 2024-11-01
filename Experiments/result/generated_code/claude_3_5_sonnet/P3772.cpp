#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 200005

double p[MAXN], q[MAXN];
double f[MAXN][2], g[MAXN][2];
int known[MAXN];

void init(int n) {
    for (int i = n; i >= 1; i--) {
        if (i == n) {
            f[i][0] = f[i][1] = 0;
            g[i][0] = g[i][1] = 1;
        } else {
            f[i][1] = p[i+1] * (f[i+1][1] + 1) + (1 - p[i+1]) * f[i+1][0];
            f[i][0] = q[i+1] * (f[i+1][1] + 1) + (1 - q[i+1]) * f[i+1][0];
            g[i][1] = p[i+1] * g[i+1][1] + (1 - p[i+1]) * g[i+1][0];
            g[i][0] = q[i+1] * g[i+1][1] + (1 - q[i+1]) * g[i+1][0];
        }
    }
}

double solve(int n) {
    double fp = 0, gp = 1;
    for (int i = 1; i <= n; i++) {
        if (known[i] == -1) {
            double nfp = p[i] * (fp + 1) + (1 - p[i]) * fp;
            double ngp = p[i] * gp + (1 - p[i]) * gp;
            fp = nfp;
            gp = ngp;
        } else if (known[i] == 1) {
            fp = f[i][1] + 1;
            gp = g[i][1];
        } else {
            fp = f[i][0];
            gp = g[i][0];
        }
    }
    return fp;
}

int main() {
    int n, m;
    char type[5];
    scanf("%d %d %s", &n, &m, type);

    scanf("%lf", &p[1]);
    for (int i = 2; i <= n; i++)
        scanf("%lf %lf", &p[i], &q[i]);

    init(n);
    memset(known, -1, sizeof(known));

    char op[5];
    int i, c;
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'a') {
            scanf("%d %d", &i, &c);
            known[i] = c;
        } else {
            scanf("%d", &i);
            known[i] = -1;
        }
        printf("%.6f\n", solve(n));
    }

    return 0;
}