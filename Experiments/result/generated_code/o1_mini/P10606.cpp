#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp_desc(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia < ib) return 1;
    else if (ia > ib) return -1;
    else return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int*)malloc((n+2)*sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    
    int *x = (int*)malloc(m * sizeof(int));
    for(int i=0;i<m;i++){
        int tmp_x, tmp_y;
        scanf("%d %d", &tmp_x, &tmp_y);
        x[i] = tmp_x;
    }
    
    qsort(x, m, sizeof(int), cmp_desc);
    
    // Remove duplicates
    int *uniq = (int*)malloc(m * sizeof(int));
    int uniq_size=0;
    if(m >0){
        uniq[uniq_size++] = x[0];
        for(int i=1;i<m;i++) {
            if(x[i] != x[i-1]){
                uniq[uniq_size++] = x[i];
            }
        }
    }
    
    // Precompute min_a_p and min_p
    ll *min_a_p = (ll*)malloc((n+2)*sizeof(ll));
    int *min_p = (int*)malloc((n+2)*sizeof(int));
    ll current_min = 1e18;
    int current_p = n+1;
    for(int p=n; p>=1; p--){
        if((ll)a[p] < current_min){
            current_min = a[p];
            current_p = p;
        }
        min_a_p[p] = current_min;
        min_p[p] = current_p;
    }
    
    ll total =0;
    int p_max=0;
    for(int i=0;i<uniq_size;i++){
        int xi = uniq[i];
        if(p_max < xi){
            int p_selected = min_p[xi];
            total += (ll)a[p_selected];
            if(p_selected > p_max) p_max = p_selected;
        }
    }
    
    printf("%lld\n", total);
    
    free(a);
    free(x);
    free(uniq);
    free(min_a_p);
    free(min_p);
    return 0;
}