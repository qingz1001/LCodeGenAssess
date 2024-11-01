#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll val;
    int index;
} Element;

// Comparator for descending sort
int cmp_desc(const void *a, const void *b) {
    Element *ea = (Element *)a;
    Element *eb = (Element *)b;
    if (eb->val > ea->val) return 1;
    else if (eb->val < ea->val) return -1;
    else return 0;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, K, L;
        scanf("%d %d %d", &n, &K, &L);
        ll *a = (ll *)malloc(n * sizeof(ll));
        ll *b = (ll *)malloc(n * sizeof(ll));
        for(int i=0;i<n;i++) scanf("%lld", &a[i]);
        for(int i=0;i<n;i++) scanf("%lld", &b[i]);
        
        // Prepare sorted_a
        Element *sorted_a = (Element *)malloc(n * sizeof(Element));
        for(int i=0;i<n;i++){
            sorted_a[i].val = a[i];
            sorted_a[i].index = i;
        }
        qsort(sorted_a, n, sizeof(Element), cmp_desc);
        
        // Prepare sorted_b
        Element *sorted_b = (Element *)malloc(n * sizeof(Element));
        for(int i=0;i<n;i++){
            sorted_b[i].val = b[i];
            sorted_b[i].index = i;
        }
        qsort(sorted_b, n, sizeof(Element), cmp_desc);
        
        // Prepare sorted_ab
        Element *sorted_ab = (Element *)malloc(n * sizeof(Element));
        for(int i=0;i<n;i++){
            sorted_ab[i].val = a[i] + b[i];
            sorted_ab[i].index = i;
        }
        qsort(sorted_ab, n, sizeof(Element), cmp_desc);
        
        // Compute sum_a_sorted and sum_b_sorted
        ll sum_a_sorted = 0;
        for(int i=0;i<K && i<n;i++) sum_a_sorted += sorted_a[i].val;
        
        ll sum_b_sorted = 0;
        for(int i=0;i<K && i<n;i++) sum_b_sorted += sorted_b[i].val;
        
        // Create top_a_set
        char *top_a_set = (char *)calloc(n, sizeof(char));
        for(int i=0;i<K && i<n;i++) {
            top_a_set[sorted_a[i].index] = 1;
        }
        
        // Create top_b_set
        char *top_b_set = (char *)calloc(n, sizeof(char));
        for(int i=0;i<K && i<n;i++) {
            top_b_set[sorted_b[i].index] = 1;
        }
        
        // Initialize prefix sums
        ll *prefix_sum_a_common = (ll *)calloc(K+1, sizeof(ll));
        ll *prefix_sum_b_common = (ll *)calloc(K+1, sizeof(ll));
        ll *sum_overlap_a = (ll *)calloc(K+1, sizeof(ll));
        ll *sum_overlap_b = (ll *)calloc(K+1, sizeof(ll));
        
        for(int x=1; x<=K && x<=n; x++){
            int idx = sorted_ab[x-1].index;
            prefix_sum_a_common[x] = prefix_sum_a_common[x-1] + a[idx];
            prefix_sum_b_common[x] = prefix_sum_b_common[x-1] + b[idx];
            if(top_a_set[idx]) sum_overlap_a[x] = sum_overlap_a[x-1] + a[idx];
            else sum_overlap_a[x] = sum_overlap_a[x-1];
            if(top_b_set[idx]) sum_overlap_b[x] = sum_overlap_b[x-1] + b[idx];
            else sum_overlap_b[x] = sum_overlap_b[x-1];
        }
        
        // Compute the maximum total sum for x from L to K
        ll max_total = 0;
        for(int x=L; x<=K && x<=n; x++){
            ll total = sum_a_sorted + sum_b_sorted + prefix_sum_a_common[x] + prefix_sum_b_common[x] - sum_overlap_a[x] - sum_overlap_b[x];
            if(total > max_total) max_total = total;
        }
        
        printf("%lld\n", max_total);
        
        // Free memory
        free(a);
        free(b);
        free(sorted_a);
        free(sorted_b);
        free(sorted_ab);
        free(top_a_set);
        free(top_b_set);
        free(prefix_sum_a_common);
        free(prefix_sum_b_common);
        free(sum_overlap_a);
        free(sum_overlap_b);
    }
    return 0;
}