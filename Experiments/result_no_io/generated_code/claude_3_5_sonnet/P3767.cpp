#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int u, v, t;
} Operation;

int n, m;
Operation ops[MAXM];
int parent[MAXN], rank[MAXN];
int version[MAXM];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

int union_sets(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return 0;
    if (rank[px] < rank[py]) {
        parent[px] = py;
    } else if (rank[px] > rank[py]) {
        parent[py] = px;
    } else {
        parent[py] = px;
        rank[px]++;
    }
    return 1;
}

void copy_state(int src, int dst) {
    memcpy(&parent[dst * n + 1], &parent[src * n + 1], n * sizeof(int));
    memcpy(&rank[dst * n + 1], &rank[src * n + 1], n * sizeof(int));
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= m; i++) {
        int k, t, u, v;
        scanf("%d %d", &k, &t);
        
        if (t == 1 || t == 2) {
            scanf("%d %d", &u, &v);
            ops[i] = (Operation){u, v, t};
        } else {
            scanf("%d", &u);
            ops[i] = (Operation){u, 0, t};
        }
        
        version[i] = k;
    }
    
    for (int i = 0; i <= m; i++) {
        init(n);
    }
    
    for (int i = 1; i <= m; i++) {
        copy_state(version[i], i);
        
        if (ops[i].t == 1 || ops[i].t == 2) {
            int u = ops[i].u, v = ops[i].v;
            int pu = find(u + i * n), pv = find(v + i * n);
            
            if (pu == pv) {
                printf("naive\n");
            } else {
                if (union_sets(u + i * n, v + i * n + n * MAXM * (ops[i].t - 1))) {
                    printf("excited\n");
                } else {
                    printf("naive\n");
                }
            }
        } else {
            int x = ops[i].u;
            printf("%s\n", ops[x].t == 3 ? "naive" : "excited");
        }
    }
    
    return 0;
}