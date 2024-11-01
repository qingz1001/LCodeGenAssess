#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 200005
#define EPS 1e-9

double p[MAXN], q[MAXN];
double f[MAXN][2], g[MAXN][2];
int known[MAXN];

int n, m;

void init() {
    f[1][1] = p[1];
    f[1][0] = 1 - p[1];
    g[1][1] = g[1][0] = 1;
    
    for (int i = 2; i <= n; i++) {
        f[i][1] = f[i-1][1] * p[i] + f[i-1][0] * q[i];
        f[i][0] = f[i-1][1] * (1-p[i]) + f[i-1][0] * (1-q[i]);
        g[i][1] = g[i-1][1] * p[i] + g[i-1][0] * q[i];
        g[i][0] = g[i-1][1] * (1-p[i]) + g[i-1][0] * (1-q[i]);
    }
}

double calc() {
    double res = 0;
    double prob = 1;
    
    for (int i = 1; i <= n; i++) {
        if (known[i] == 1) {
            res += prob * g[n-i+1][1];
            prob *= f[i][1] / f[i-1][1];
        } else if (known[i] == 0) {
            res += 0;
            prob *= f[i][0] / f[i-1][0];
        } else {
            res += prob * f[i][1];
        }
    }
    
    return res;
}

int main() {
    char type[10];
    scanf("%d%d%s", &n, &m, type);
    
    scanf("%lf", &p[1]);
    for (int i = 2; i <= n; i++) {
        scanf("%lf%lf", &p[i], &q[i]);
    }
    
    init();
    
    char op[5];
    int x, y;
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'a') {
            scanf("%d%d", &x, &y);
            known[x] = y + 1;
        } else {
            scanf("%d", &x);
            known[x] = 0;
        }
        printf("%.10f\n", calc());
    }
    
    return 0;
}