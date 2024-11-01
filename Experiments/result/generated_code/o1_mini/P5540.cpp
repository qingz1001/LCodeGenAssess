#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, a, b;
} Edge;

int cmp_a(const void *x, const void *y) {
    Edge *e1 = (Edge *)x;
    Edge *e2 = (Edge *)y;
    if (e1->a != e2->a)
        return e1->a - e2->a;
    return e1->b - e2->b;
}

int cmp_b(const void *x, const void *y) {
    Edge *e1 = (Edge *)x;
    Edge *e2 = (Edge *)y;
    if (e1->b != e2->b)
        return e1->b - e2->b;
    return e1->a - e2->a;
}

int parent[201];

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void krusky(int n, Edge edges[], int m, long long *sum_a, long long *sum_b) {
    for(int i=0;i<n;i++) parent[i]=i;
    *sum_a = 0;
    *sum_b = 0;
    int count = 0;
    for(int i=0;i<m && count < n-1;i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int pu = find_set(u);
        int pv = find_set(v);
        if(pu != pv){
            parent[pu] = pv;
            *sum_a += edges[i].a;
            *sum_b += edges[i].b;
            count++;
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge edges[10000];
    for(int i=0;i<m;i++) {
        scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
    }
    // First sort by a, then by b
    qsort(edges, m, sizeof(Edge), cmp_a);
    long long sum_a1, sum_b1;
    krusky(n, edges, m, &sum_a1, &sum_b1);
    // Second sort by b, then by a
    qsort(edges, m, sizeof(Edge), cmp_b);
    long long sum_a2, sum_b2;
    krusky(n, edges, m, &sum_a2, &sum_b2);
    // Compare A*B
    long long prod1 = sum_a1 * sum_b1;
    long long prod2 = sum_a2 * sum_b2;
    if(prod1 < prod2 || (prod1 == prod2 && sum_a1 < sum_a2)){
        printf("%lld %lld\n", sum_a1, sum_b1);
    }
    else{
        printf("%lld %lld\n", sum_a2, sum_b2);
    }
}