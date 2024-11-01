#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int type; // 1: u生v, 2: u克v
    int u, v;
} Spell;

Spell spells[MAXM];
int parent[MAXN];
int rank[MAXN];
int color[MAXN]; // 0: 未染色, 1: 金, 2: 木, 3: 水, 4: 火, 5: 土

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

bool dfs(int node, int c) {
    color[node] = c;
    int nextColor = (c == 1) ? 2 : 1;
    for (int i = 0; i < MAXM; i++) {
        if (spells[i].type == 1 && spells[i].u == node) {
            if (color[spells[i].v] == c) return false;
            if (color[spells[i].v] == 0 && !dfs(spells[i].v, nextColor)) return false;
        } else if (spells[i].type == 2 && spells[i].u == node) {
            if (color[spells[i].v] == nextColor) return false;
            if (color[spells[i].v] == 0 && !dfs(spells[i].v, c)) return false;
        }
    }
    return true;
}

bool check() {
    for (int i = 1; i <= MAXN; i++) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) return false;
        }
    }
    return true;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        rank[i] = 0;
        color[i] = 0;
    }

    int k, t, u, v, x;
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &k, &t);
        if (t == 1 || t == 2) {
            scanf("%d %d", &u, &v);
            spells[i] = (Spell){t, u, v};
            if (t == 1) {
                unionSet(u, v);
            }
        } else if (t == 3) {
            scanf("%d", &x);
            spells[i] = spells[x];
        }

        if (check()) {
            printf("excited\n");
        } else {
            printf("naive\n");
        }
    }

    return 0;
}