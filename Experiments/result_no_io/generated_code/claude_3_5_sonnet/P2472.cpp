#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_R 20
#define MAX_C 20
#define INF 0x3f3f3f3f

int r, c, d;
int h[MAX_R][MAX_C];
char lizard[MAX_R][MAX_C];
int graph[MAX_R * MAX_C + 2][MAX_R * MAX_C + 2];
int match[MAX_R * MAX_C + 2];
int vis[MAX_R * MAX_C + 2];

int dfs(int u) {
    for (int v = 1; v <= r * c + 1; v++) {
        if (graph[u][v] && !vis[v]) {
            vis[v] = 1;
            if (match[v] == 0 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int hungarian() {
    int res = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= r * c; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) res++;
    }
    return res;
}

int main() {
    scanf("%d %d %d", &r, &c, &d);
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &h[i][j]);
        }
    }
    
    int lizard_count = 0;
    for (int i = 0; i < r; i++) {
        scanf("%s", lizard[i]);
        for (int j = 0; j < c; j++) {
            if (lizard[i][j] == 'L') lizard_count++;
        }
    }
    
    memset(graph, 0, sizeof(graph));
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (lizard[i][j] == 'L') {
                int u = i * c + j + 1;
                if (i == 0 || i == r - 1 || j == 0 || j == c - 1) {
                    graph[u][r * c + 1] = 1;
                }
                for (int ni = 0; ni < r; ni++) {
                    for (int nj = 0; nj < c; nj++) {
                        if (h[ni][nj] > 0 && h[i][j] > 0 && (i != ni || j != nj)) {
                            int dist = (i - ni) * (i - ni) + (j - nj) * (j - nj);
                            if (dist <= d * d) {
                                int v = ni * c + nj + 1;
                                graph[u][v] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    
    int max_flow = hungarian();
    printf("%d\n", lizard_count - max_flow);
    
    return 0;
}