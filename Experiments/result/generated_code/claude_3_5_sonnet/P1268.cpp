#include <stdio.h>
#include <string.h>

#define MAX_N 30
#define INF 0x3f3f3f3f

int n;
int M[MAX_N][MAX_N];
int parent[MAX_N];
int weight[MAX_N];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        parent[x] = y;
    }
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
        weight[i] = INF;
    }
    
    int total_weight = 0;
    
    for (int k = 0; k < n - 1; k++) {
        int min_weight = INF;
        int x = -1, y = -1;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (find(i) != find(j) && M[i][j] - weight[i] - weight[j] < min_weight) {
                    min_weight = M[i][j] - weight[i] - weight[j];
                    x = i;
                    y = j;
                }
            }
        }
        
        unite(x, y);
        total_weight += min_weight;
        
        for (int i = 0; i < n; i++) {
            if (find(i) == find(x)) {
                weight[i] = (weight[i] < weight[x]) ? weight[i] : weight[x];
            }
            if (find(i) == find(y)) {
                weight[i] = (weight[i] < weight[y]) ? weight[i] : weight[y];
            }
        }
        
        weight[x] += min_weight / 2;
        weight[y] += min_weight / 2;
        if (min_weight % 2 == 1) {
            weight[x]++;
        }
    }
    
    printf("%d\n", total_weight);
    
    return 0;
}