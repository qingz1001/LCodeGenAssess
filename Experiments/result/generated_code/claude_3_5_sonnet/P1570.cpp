#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 200

typedef struct {
    double ratio;
    int index;
} Ingredient;

int compare(const void* a, const void* b) {
    Ingredient* ia = (Ingredient*)a;
    Ingredient* ib = (Ingredient*)b;
    if (ia->ratio > ib->ratio) return -1;
    if (ia->ratio < ib->ratio) return 1;
    return 0;
}

int main() {
    int n, m;
    int v[MAX_N], c[MAX_N];
    Ingredient ingredients[MAX_N];
    
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
        ingredients[i].ratio = (double)v[i] / c[i];
        ingredients[i].index = i;
    }
    
    qsort(ingredients, n, sizeof(Ingredient), compare);
    
    double total_v = 0, total_c = 0;
    for (int i = 0; i < m; i++) {
        int idx = ingredients[i].index;
        total_v += v[idx];
        total_c += c[idx];
    }
    
    printf("%.3f\n", total_v / total_c);
    
    return 0;
}