#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to compute the number of submissions for a given n
ll compute_f(ll n, ll *x, int l) {
    ll code = 0;
    ll submissions = 0;
    for(int i=0;i<l;i++) {
        if(x[i] >= 0){
            code += x[i];
        }
        else{
            code += x[i]; // x[i] is negative
            if(code < 0){
                code = 0;
            }
        }
        if(code >= n){
            submissions++;
            code = 0;
        }
    }
    return submissions;
}

// Binary search to find the smallest n where f(n) <= k
ll find_left_n(ll left, ll right, ll k, ll *x, int l) {
    ll res = right + 1;
    while(left <= right){
        ll mid = left + (right - left) / 2;
        ll tmp = compute_f(mid, x, l);
        if(tmp <= k){
            res = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    return res;
}

// Binary search to find the smallest n where f(n) < k
ll find_right_n(ll left, ll right, ll k, ll *x, int l) {
    ll res = right + 1;
    while(left <= right){
        ll mid = left + (right - left) / 2;
        ll tmp = compute_f(mid, x, l);
        if(tmp < k){
            res = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    return res;
}

int main(){
    int l;
    ll k;
    if(scanf("%d %lld", &l, &k)!=2){
        return 0;
    }
    ll *x = (ll*)malloc(sizeof(ll)*l);
    for(int i=0;i<l;i++){
        scanf("%lld", &x[i]);
    }
    // Compute sum_max
    ll code =0;
    ll sum_max =0;
    for(int i=0;i<l;i++){
        if(x[i] >=0){
            code +=x[i];
        }
        else{
            code +=x[i];
            if(code <0){
                code =0;
            }
        }
        if(code > sum_max){
            sum_max = code;
        }
    }
    // Binary search for left_n and right_n
    ll left_n = find_left_n(1, sum_max +1, k, x, l);
    ll right_n = find_right_n(1, sum_max +1, k, x, l);
    // Determine the range where f(n) == k
    if(left_n > sum_max +1){
        if(k ==0){
            printf("%lld %lld\n", sum_max +1, sum_max +1);
        }
        else{
            printf("-1\n");
        }
    }
    else{
        if(right_n > sum_max +1 +1){
            right_n = sum_max +2;
        }
        if(left_n <= (right_n -1)){
            // Ensure right_n -1 does not exceed sum_max +1
            if(right_n -1 > sum_max +1){
                printf("-1\n");
                free(x);
                return 0;
            }
            printf("%lld %lld\n", left_n, right_n -1);
        }
        else{
            printf("-1\n");
        }
    }
    free(x);
    return 0;
}