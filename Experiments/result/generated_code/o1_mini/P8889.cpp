#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator function for qsort and bsearch
int cmp(const void *a, const void *b) {
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    ll *a = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    
    ll *b = (ll*)malloc(m * sizeof(ll));
    for(int i=0;i<m;i++) scanf("%lld", &b[i]);
    
    qsort(b, m, sizeof(ll), cmp);
    
    int count = 0;
    int in_fragment = 0;
    for(int i=0;i<n;i++){
        if(bsearch(&a[i], b, m, sizeof(ll), cmp)){
            in_fragment = 0;
        }
        else{
            if(!in_fragment){
                count++;
                in_fragment = 1;
            }
        }
    }
    
    printf("%d\n", count);
    
    free(a);
    free(b);
    return 0;
}