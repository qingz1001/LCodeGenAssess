#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int index;
    ll value;
} Element;

int cmp_desc_a(const void *a, const void *b) {
    Element *ea = (Element *)a;
    Element *eb = (Element *)b;
    if (ea->value != eb->value)
        return (ea->value > eb->value) ? -1 : 1;
    return ea->index - eb->index;
}

int cmp_desc_c(const void *a, const void *b) {
    Element *ea = (Element *)a;
    Element *eb = (Element *)b;
    if (ea->value != eb->value)
        return (ea->value > eb->value) ? -1 : 1;
    return ea->index - eb->index;
}

typedef struct {
    int size;
    ll *tree;
} BIT;

BIT* create_BIT(int size){
    BIT* bit = (BIT*) malloc(sizeof(BIT));
    bit->size = size;
    bit->tree = (ll*) calloc(size + 2, sizeof(ll));
    return bit;
}

void update_BIT(BIT* bit, int idx, ll val){
    while(idx <= bit->size){
        bit->tree[idx] += val;
        idx += idx & -idx;
    }
}

ll query_BIT(BIT* bit, int idx){
    ll res = 0;
    while(idx > 0){
        res += bit->tree[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, K, L;
        scanf("%d %d %d", &n, &K, &L);
        ll *a = (ll*) malloc((n+1)*sizeof(ll));
        ll *b = (ll*) malloc((n+1)*sizeof(ll));
        for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
        for(int i=1;i<=n;i++) scanf("%lld", &b[i]);
        
        Element *c_elements = (Element*) malloc(n * sizeof(Element));
        Element *a_elements = (Element*) malloc(n * sizeof(Element));
        Element *b_elements = (Element*) malloc(n * sizeof(Element));
        for(int i=0;i<n;i++){
            c_elements[i].index = i+1;
            c_elements[i].value = a[i+1] + b[i+1];
            a_elements[i].index = i+1;
            a_elements[i].value = a[i+1];
            b_elements[i].index = i+1;
            b_elements[i].value = b[i+1];
        }
        
        qsort(c_elements, n, sizeof(Element), cmp_desc_c);
        qsort(a_elements, n, sizeof(Element), cmp_desc_a);
        qsort(b_elements, n, sizeof(Element), cmp_desc_a);
        
        // Prefix sums
        ll *prefix_c = (ll*) calloc((K+2), sizeof(ll));
        for(int t=1;t<=K;t++) prefix_c[t] = prefix_c[t-1] + c_elements[t-1].value;
        
        ll *prefix_a = (ll*) calloc((K+2), sizeof(ll));
        for(int t=1;t<=K;t++) prefix_a[t] = prefix_a[t-1] + a_elements[t-1].value;
        
        ll *prefix_b = (ll*) calloc((K+2), sizeof(ll));
        for(int t=1;t<=K;t++) prefix_b[t] = prefix_b[t-1] + b_elements[t-1].value;
        
        // Position arrays
        int *pos_c = (int*) calloc((n+2), sizeof(int));
        int *pos_a_sorted = (int*) calloc((n+2), sizeof(int));
        int *pos_b_sorted = (int*) calloc((n+2), sizeof(int));
        for(int t=0;t<n;t++){
            pos_c[c_elements[t].index] = t+1;
            pos_a_sorted[a_elements[t].index] = t+1;
            pos_b_sorted[b_elements[t].index] = t+1;
        }
        
        // Initialize BITs
        BIT* bit_a = create_BIT(K);
        BIT* bit_b = create_BIT(K);
        ll *sum_a_overlap = (ll*) calloc((K+2), sizeof(ll));
        ll *sum_b_overlap = (ll*) calloc((K+2), sizeof(ll));
        
        for(int t=1;t<=K;t++){
            int idx = c_elements[t-1].index;
            int pos_a = pos_a_sorted[idx];
            if(pos_a <= (K - t)){
                update_BIT(bit_a, pos_a, a[idx]);
            }
            sum_a_overlap[t] = query_BIT(bit_a, K - t);
            
            int pos_b = pos_b_sorted[idx];
            if(pos_b <= (K - t)){
                update_BIT(bit_b, pos_b, b[idx]);
            }
            sum_b_overlap[t] = query_BIT(bit_b, K - t);
        }
        
        // Calculate maximum
        ll max_sum = 0;
        for(int t=L;t<=K;t++){
            ll total = prefix_c[t];
            if(K - t > 0){
                total += prefix_a[K - t] - sum_a_overlap[t];
                total += prefix_b[K - t] - sum_b_overlap[t];
            }
            if(total > max_sum) max_sum = total;
        }
        
        printf("%lld\n", max_sum);
        
        // Free memory
        free(a);
        free(b);
        free(c_elements);
        free(a_elements);
        free(b_elements);
        free(prefix_c);
        free(prefix_a);
        free(prefix_b);
        free(pos_c);
        free(pos_a_sorted);
        free(pos_b_sorted);
        free(sum_a_overlap);
        free(sum_b_overlap);
        free(bit_a->tree);
        free(bit_a);
        free(bit_b->tree);
        free(bit_b);
    }
    return 0;
}