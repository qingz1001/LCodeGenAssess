#include <stdio.h>
#include <stdbool.h>

int main() {
    int l, m;
    scanf("%d %d", &l, &m);
    
    bool trees[l + 1];
    for (int i = 0; i <= l; i++) {
        trees[i] = true;
    }
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        for (int j = u; j <= v; j++) {
            trees[j] = false;
        }
    }
    
    int remaining_trees = 0;
    for (int i = 0; i <= l; i++) {
        if (trees[i]) {
            remaining_trees++;
        }
    }
    
    printf("%d\n", remaining_trees);
    
    return 0;
}