#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int N, M;
int parent[MAXN], rank[MAXN];
int color[MAXN];
int history[MAXM][4];
int cnt = 0;

void init() {
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        rank[i] = 0;
        color[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y])
            rank[x]++;
    }
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= M; i++) {
        int k, t, u, v;
        scanf("%d %d", &k, &t);
        
        if (t == 1 || t == 2) {
            scanf("%d %d", &u, &v);
            history[i][0] = k;
            history[i][1] = t;
            history[i][2] = u;
            history[i][3] = v;
        } else {
            scanf("%d", &u);
            history[i][0] = k;
            history[i][1] = t;
            history[i][2] = u;
        }
        
        init();
        int valid = 1;
        
        for (int j = 1; j <= i; j++) {
            if (history[j][1] == 3) continue;
            
            int a = history[j][2], b = history[j][3];
            int pa = find(a), pb = find(b);
            
            if (history[j][1] == 1) {
                if (color[pa] == color[pb] && color[pa] != 0) {
                    valid = 0;
                    break;
                }
                if (color[pa] == 0 && color[pb] != 0) {
                    color[pa] = (color[pb] % 5) + 1;
                } else if (color[pa] != 0 && color[pb] == 0) {
                    color[pb] = (color[pa] + 3) % 5 + 1;
                }
                unite(a, b);
            } else if (history[j][1] == 2) {
                if (color[pa] == color[pb] && color[pa] != 0) {
                    valid = 0;
                    break;
                }
                if (color[pa] == 0 && color[pb] != 0) {
                    color[pa] = (color[pb] + 1) % 5 + 1;
                } else if (color[pa] != 0 && color[pb] == 0) {
                    color[pb] = (color[pa] + 1) % 5 + 1;
                }
                unite(a, b);
            }
        }
        
        printf("%s\n", valid ? "excited" : "naive");
    }
    
    return 0;
}