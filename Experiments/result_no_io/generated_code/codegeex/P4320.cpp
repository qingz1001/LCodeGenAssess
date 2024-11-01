#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005
#define MAXM 1000005

int n, m, q;
int u[MAXM], v[MAXM];
int degree[MAXN];
int visited[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u[i], &v[i]);
        degree[u[i]]++;
        degree[v[i]]++;
    }

    int root = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            root = i;
            break;
        }
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        int minDegree = degree[s] < degree[t] ? degree[s] : degree[t];
        int ans = minDegree;

        for (int j = 1; j <= n; j++) {
            visited[j] = 0;
        }

        int current = s;
        while (current != t) {
            visited[current] = 1;
            int next = -1;
            for (int j = 0; j < m; j++) {
                if ((u[j] == current && !visited[v[j]]) || (v[j] == current && !visited[u[j]])) {
                    next = (u[j] == current) ? v[j] : u[j];
                    break;
                }
            }
            current = next;
            ans++;
        }

        printf("%d\n", ans);
    }

    return 0;
}