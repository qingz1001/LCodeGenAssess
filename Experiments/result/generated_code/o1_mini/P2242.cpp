#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator for descending order
int cmp_desc(const void *a, const void *b) {
    ll val1 = *(ll*)a;
    ll val2 = *(ll*)b;
    if(val2 > val1) return 1;
    else if(val2 < val1) return -1;
    else return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ll pos[n];
    for(int i=0;i<n;i++) scanf("%lld", &pos[i]);
    if(n ==0){
        printf("0");
        return 0;
    }
    ll gaps[n-1];
    for(int i=1;i<n;i++) gaps[i-1] = pos[i] - pos[i-1] -1;
    qsort(gaps, n-1, sizeof(ll), cmp_desc);
    ll sum =0;
    for(int i=0;i<m-1 && i<n-1;i++) sum += gaps[i];
    ll total = pos[n-1] - pos[0] +1;
    ll result = total - sum;
    printf("%lld", result);
    return 0;
}