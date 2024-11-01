#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int degree[MAXN];
int red_edges[MAXN][MAXN];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        red_edges[u][v] = 1;
        red_edges[v][u] = 1;
        degree[u]++;
        degree[v]++;
    }
    
    long long blue_keys = 0;
    long long red_keys = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!red_edges[i][j]) {
                for (int k = j + 1; k <= n; k++) {
                    if (!red_edges[i][k] && !red_edges[j][k]) {
                        for (int l = k + 1; l <= n; l++) {
                            if (!red_edges[i][l] && !red_edges[j][l] && !red_edges[k][l]) {
                                blue_keys++;
                            }
                        }
                    }
                }
            } else {
                for (int k = j + 1; k <= n; k++) {
                    if (red_edges[i][k] && red_edges[j][k]) {
                        for (int l = k + 1; l <= n; l++) {
                            if (red_edges[i][l] && red_edges[j][l] && red_edges[k][l]) {
                                red_keys++;
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("%lld\n", abs(blue_keys - red_keys));
    
    return 0;
}