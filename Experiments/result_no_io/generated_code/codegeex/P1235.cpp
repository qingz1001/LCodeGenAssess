#include <stdio.h>

int n, k, m;
int parent[301], child[301][301];

double similarity(int x, int y) {
    if (x == y) return 1.0;
    if (parent[x] == 0 && parent[y] == 0) return 0.0;
    if (parent[x] == 0) {
        double sim = similarity(x, parent[y]);
        for (int i = 1; i <= n; i++) {
            if (child[i][parent[y]] == x) {
                sim = 0.5 * sim + 0.5 * similarity(x, i);
                break;
            }
        }
        return sim;
    }
    if (parent[y] == 0) {
        double sim = similarity(y, parent[x]);
        for (int i = 1; i <= n; i++) {
            if (child[i][parent[x]] == y) {
                sim = 0.5 * sim + 0.5 * similarity(i, y);
                break;
            }
        }
        return sim;
    }
    double sim = 0.5 * similarity(parent[x], parent[y]);
    for (int i = 1; i <= n; i++) {
        if (child[i][parent[x]] == x && child[i][parent[y]] == y) {
            sim += 0.25 * similarity(x, i) * similarity(y, i);
        }
        if (child[i][parent[x]] == x && child[i][parent[y]] != y) {
            sim += 0.5 * similarity(x, i) * similarity(y, parent[y]);
        }
        if (child[i][parent[x]] != x && child[i][parent[y]] == y) {
            sim += 0.5 * similarity(x, parent[x]) * similarity(y, i);
        }
    }
    return sim;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        parent[a] = b;
        child[b][c] = a;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        double sim = similarity(x, y);
        printf("%.3f%%\n", sim * 100);
    }
    return 0;
}