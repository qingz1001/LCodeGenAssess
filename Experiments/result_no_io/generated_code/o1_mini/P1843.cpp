#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll n, a, b;
ll *w;

int cmp(const void *x, const void *y){
    ll a_val = *(ll*)x;
    ll b_val = *(ll*)y;
    if(a_val < b_val) return -1;
    if(a_val > b_val) return 1;
    return 0;
}

int is_possible(ll t){
    if(t == 0){
        for(int i=0;i<n;i++) if(w[i] >0) return 0;
        return 1;
    }
    ll count =0;
    for(int i=n-1;i>=0;i--){
        if(w[i] > a*t){
            if(w[i] > (a + b)*t) return 0;
            count++;
            if(count > t) return 0;
        }
    }
    return 1;
}

int main(){
    scanf("%lld %lld %lld", &n, &a, &b);
    w = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &w[i]);
    qsort(w, n, sizeof(ll), cmp);
    ll left=0, right=0;
    if(n==0){
        printf("0");
        return 0;
    }
    // Upper bound for t
    right = 0;
    for(int i=0;i<n;i++) {
        ll tmp = (w[i] + a + b -1)/(a + b);
        if(tmp > right) right = tmp;
    }
    right += n;
    ll ans = right;
    while(left <= right){
        ll mid = left + (right - left)/2;
        if(is_possible(mid)){
            ans = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld", ans);
    free(w);
    return 0;
}