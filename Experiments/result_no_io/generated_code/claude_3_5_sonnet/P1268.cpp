#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30
#define INF 1000000000

int n;
int M[MAX_N][MAX_N];
int parent[MAX_N];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) parent[x] = y;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        M[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &M[i][j]);
            M[j][i] = M[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int weight = 0;
    for (int k = 0; k < n - 1; k++) {
        int min_dist = INF;
        int x = -1, y = -1;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (find(i) != find(j) && M[i][j] < min_dist) {
                    min_dist = M[i][j];
                    x = i;
                    y = j;
                }
            }
        }
        
        unite(x, y);
        weight += min_dist;
    }

    printf("%d\n", weight);
    return 0;
}