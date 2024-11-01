#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 7

char map[MAXN][MAXM];
int fa[MAXN * MAXM];
int cnt[MAXN * MAXM];
int n, m;

int find(int x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        fa[x] = y;
        cnt[y] += cnt[x];
    }
}

int getId(int i, int j) {
    return i * m + j;
}

void init() {
    for (int i = 0; i < n * m; i++) {
        fa[i] = i;
        cnt[i] = 0;
    }
}

void update(int x, int y) {
    int id = getId(x, y);
    if (map[x][y] == 'O') cnt[find(id)] = 1;
    if (x > 0 && (map[x-1][y] == '+' || map[x-1][y] == '|' || map[x-1][y] == 'O') && 
        (map[x][y] == '+' || map[x][y] == '|' || map[x][y] == 'O'))
        unite(id, getId(x-1, y));
    if (y > 0 && (map[x][y-1] == '+' || map[x][y-1] == '-' || map[x][y-1] == 'O') && 
        (map[x][y] == '+' || map[x][y] == '-' || map[x][y] == 'O'))
        unite(id, getId(x, y-1));
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", map[i]);
    
    init();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            update(i, j);
    
    int q;
    scanf("%d", &q);
    while (q--) {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'C') {
            int i, j;
            char k;
            scanf("%d%d %c", &i, &j, &k);
            i--; j--;
            map[i][j] = k;
            for (int x = i-1; x <= i+1; x++)
                for (int y = j-1; y <= j+1; y++)
                    if (x >= 0 && x < n && y >= 0 && y < m) {
                        int id = getId(x, y);
                        fa[id] = id;
                        cnt[id] = 0;
                    }
            for (int x = i-1; x <= i+1; x++)
                for (int y = j-1; y <= j+1; y++)
                    if (x >= 0 && x < n && y >= 0 && y < m)
                        update(x, y);
        } else {
            int l, r, ans = 0;
            scanf("%d%d", &l, &r);
            l--; r--;
            for (int i = l; i <= r; i++)
                for (int j = 0; j < m; j++)
                    if (cnt[find(getId(i, j))] > 0) {
                        ans++;
                        cnt[find(getId(i, j))] = 0;
                    }
            printf("%d\n", ans);
            for (int i = l; i <= r; i++)
                for (int j = 0; j < m; j++)
                    cnt[find(getId(i, j))] = map[i][j] == 'O';
        }
    }
    return 0;
}