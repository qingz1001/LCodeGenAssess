#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int n;
ll l, r;
ll a[12];
ll count_ans = 0;

// Comparator for descending sort
int cmp_desc(const void* x, const void* y){
    ll a_val = *(ll*)y;
    ll b_val = *(ll*)x;
    if(a_val > b_val) return 1;
    else if(a_val < b_val) return -1;
    else return 0;
}

ll dfs(int index, ll sum){
    if(index == n){
        if(sum >= l && sum <= r){
            return 1;
        }
        return 0;
    }

    if(a[index] == 1){
        if(sum > r){
            return 0;
        }
        ll start = sum >= l ? sum : l;
        if(start > r){
            return 0;
        }
        return r - start +1;
    }

    if(a[index] ==0){
        return dfs(index+1, sum);
    }

    ll cnt =0;
    ll ai = a[index];
    ll max_x = (r - sum) / ai;
    // To prevent too deep recursion, limit max_x
    // If max_x is too large, it's better to iterate in steps or find another way
    // Here, proceed with loop, assuming n <=12 and a_i reasonable
    for(ll x=0; x <= max_x; x++){
        ll new_sum = sum + x * ai;
        if(new_sum > r){
            break;
        }
        cnt += dfs(index+1, new_sum);
    }
    return cnt;
}

int main(){
    if(scanf("%d %lld %lld", &n, &l, &r)!=3){
        return 0;
    }
    for(int i=0;i<n;i++){
        scanf("%lld", &a[i]);
    }
    // Sort in descending order
    qsort(a, n, sizeof(ll), cmp_desc);
    ll result = dfs(0, 0);
    printf("%lld\n", result);
    return 0;
}