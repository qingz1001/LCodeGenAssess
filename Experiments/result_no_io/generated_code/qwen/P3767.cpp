#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

int N, M;
int operations[MAXM][4];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int check() {
    for (int i = 1; i <= N; i++) {
        if (find(i) != 1) {
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i <= N; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &operations[i][0], &operations[i][1]);
        if (operations[i][0] == 0) {
            operations[i][0] = i + 1;
        }
        if (operations[i][1] == 1) {
            scanf("%d %d", &operations[i][2], &operations[i][3]);
        } else if (operations[i][1] == 2) {
            scanf("%d %d", &operations[i][2], &operations[i][3]);
        } else if (operations[i][1] == 3) {
            scanf("%d", &operations[i][2]);
        }
    }

    for (int t = 0; t < M; t++) {
        int k = operations[t][0];
        int type = operations[t][1];
        if (type == 1 || type == 2) {
            int u = operations[t][2];
            int v = operations[t][3];
            if (type == 1) {
                union_sets(u, v);
            } else {
                union_sets(v, u);
            }
        } else if (type == 3) {
            int x = operations[t][2];
            for (int j = t - 1; j >= 0; j--) {
                if (operations[j][0] == x) {
                    if (operations[j][1] == 1) {
                        union_sets(operations[j][2], operations[j][3]);
                    } else if (operations[j][1] == 2) {
                        union_sets(operations[j][3], operations[j][2]);
                    }
                    break;
                }
            }
        }
        if (check()) {
            printf("excited\n");
        } else {
            printf("naive\n");
        }
    }

    return 0;
}