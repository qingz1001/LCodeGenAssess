#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

// Comparison function for qsort
int cmp_ll(const void *a, const void *b) {
    ll va = *(ll*)a;
    ll vb = *(ll*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    ll *a = (ll*)malloc(n * sizeof(ll));
    ll sum = 0;
    for(int i=0;i<n;i++){
        scanf("%lld", &a[i]);
        sum += a[i];
    }
    if(sum % n !=0){
        // It's guaranteed that it's possible, but just in case
        printf("-1\n");
        free(a);
        return 0;
    }
    ll target = sum / n;
    ll *ps = (ll*)malloc((n-1) * sizeof(ll));
    ll s = 0;
    for(int i=0;i<n-1;i++){
        s += a[i] - target;
        ps[i] = s;
    }
    qsort(ps, n-1, sizeof(ll), cmp_ll);
    ll median;
    if((n-1) %2 ==1){
        median = ps[(n-1)/2];
    }
    else{
        median = ps[(n-1)/2];
    }
    ll cost =0;
    for(int i=0;i<n-1;i++) {
        cost += llabs(ps[i] - median);
    }
    printf("%lld\n", cost);
    free(a);
    free(ps);
    return 0;
}