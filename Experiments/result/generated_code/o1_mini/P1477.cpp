#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

typedef struct {
    int a;
    int b;
} Edge;

// Comparator for qsort
int cmp_edge(const void *x, const void *y){
    Edge *e1 = (Edge*)x;
    Edge *e2 = (Edge*)y;
    if(e1->a != e2->a)
        return e1->a - e2->a;
    return e1->b - e2->b;
}

#define MAX 100005
#define MAX_EDGES 1000005

int parent[MAX];
ll potential_val[MAX];

// Find with path compression
int find_set(int x){
    if(parent[x] != x){
        int orig_parent = parent[x];
        parent[x] = find_set(parent[x]);
        potential_val[x] += potential_val[orig_parent];
    }
    return parent[x];
}

// GCD function
ll gcd_func(ll a, ll b){
    while(b){
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2){
        return 0;
    }
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<m;i++){
        scanf("%d %d", &edges[i].a, &edges[i].b);
    }
    // Sort edges
    qsort(edges, m, sizeof(Edge), cmp_edge);
    // Initialize Union-Find
    for(int i=1;i<=n;i++){
        parent[i] = i;
        potential_val[i] = 0;
    }
    ll G = 0;
    // Process unique edges
    int unique_m = 0;
    for(int i=0;i<m;i++){
        if(i >0 && edges[i].a == edges[i-1].a && edges[i].b == edges[i-1].b){
            continue;
        }
        // Process edges[unique_m] = edges[i]
        int a = edges[i].a;
        int b = edges[i].b;
        int root_a = find_set(a);
        int root_b = find_set(b);
        ll p_a = potential_val[a];
        ll p_b = potential_val[b];
        if(root_a != root_b){
            parent[root_a] = root_b;
            potential_val[root_a] = p_b - p_a -1;
        }
        else{
            ll t = p_a - p_b +1;
            if(t <0){
                t = -t;
            }
            if(t >0){
                G = gcd_func(G, t);
            }
        }
        unique_m++;
    }
    free(edges);
    // Determine min and max k
    if(G ==0){
        if(n >=3){
            printf("%d %d\n",  n, 3);
        }
        else{
            printf("-1 -1\n");
            return 0;
        }
    }
    else{
        // Find all divisors of G >=3
        int min_k = -1, max_k = -1;
        ll sqrtG = sqrt((double)G);
        for(ll d=1; d<=sqrtG; d++){
            if(G % d ==0){
                if(d >=3){
                    if(min_k == -1 || d < min_k){
                        min_k = d;
                    }
                    if(d >=3 && d > max_k){
                        max_k = d;
                    }
                }
                ll other = G / d;
                if(other != d && other >=3){
                    if(min_k == -1 || other < min_k){
                        min_k = other;
                    }
                    if(other >=3 && other > max_k){
                        max_k = other;
                    }
                }
            }
        }
        if(min_k == -1){
            printf("-1 -1\n");
        }
        else{
            // Find the smallest and largest divisors >=3
            // To ensure min_k is smallest and max_k is largest
            min_k = G; max_k = 1;
            for(ll d=1; d<=sqrtG; d++){
                if(G % d ==0){
                    if(d >=3){
                        if(d < min_k){
                            min_k = d;
                        }
                        if(d > max_k){
                            max_k = d;
                        }
                    }
                    ll other = G / d;
                    if(other >=3){
                        if(other < min_k){
                            min_k = other;
                        }
                        if(other > max_k){
                            max_k = other;
                        }
                    }
                }
            }
            printf("%lld %lld\n", max_k, min_k);
        }
    }
}