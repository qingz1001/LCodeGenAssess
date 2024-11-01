#include <stdio.h>
#include <string.h>
#include <math.h>

const int MAXN = 200010;
const double EPS = 1e-8;

int n, m;
double p[MAXN], q[MAXN];
char type[10];

struct Node {
    int id;
    char op;
    int val;
} nodes[MAXN];

double ans, g[MAXN];

int main() {
    scanf("%d%d%s", &n, &m, type);
    scanf("%lf", &p[1]);
    for (int i = 2; i <= n; i++) {
        scanf("%lf%lf", &p[i], &q[i]);
    }
    for (int i = 1; i <= m; i++) {
        char op[10];
        scanf("%s", op);
        if (op[0] == 'a') {
            nodes[i].op = 'a';
            scanf("%d%d", &nodes[i].id, &nodes[i].val);
        } else {
            nodes[i].op = 'd';
            scanf("%d", &nodes[i].id);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (nodes[i].op == 'a') {
            int id = nodes[i].id;
            int val = nodes[i].val;
            ans += val * p[id];
            g[id] = val ? p[id] : q[id];
        } else {
            int id = nodes[i].id;
            ans -= g[id];
            g[id] = 0.0;
        }

        double sum = 0.0;
        for (int j = 1; j <= n; j++) {
            sum += g[j];
        }
        double f = 1.0 - sum;
        for (int j = 1; j <= n; j++) {
            g[j] = g[j] / sum * f;
        }
        ans += (n - sum) * f;

        printf("%.6lf\n", ans);
    }

    return 0;
}