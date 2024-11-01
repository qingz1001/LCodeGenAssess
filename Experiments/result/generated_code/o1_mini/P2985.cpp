#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

ll N, D;
ll H[50005];
ll assign_day[50005];
ll total_H = 0;

// Function to check if a minimum happiness 't' is achievable
int can_assign(ll t) {
    ll day = 1;
    ll h_prev = 0;
    ll i = 0;
    while (i < N && day <= D) {
        ll wake = h_prev / 2;
        ll need = t > wake ? t - wake : 0;
        ll sum = 0;
        ll start = i;
        while (i < N && sum < need) {
            sum += H[i];
            i++;
        }
        if (sum < need)
            return 0;
        h_prev = wake + sum;
        day++;
    }
    if (i == N)
        return 1;
    return 0;
}

int main(){
    scanf("%lld %lld", &N, &D);
    for(ll i=0;i<N;i++){
        scanf("%lld", &H[i]);
        total_H += H[i];
    }
    ll left = 0, right = total_H + 1, mid, best = 0;
    while(left <= right){
        mid = left + (right - left) / 2;
        if(can_assign(mid)){
            best = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    // Now assign days based on best
    ll t = best;
    ll day =1;
    ll h_prev =0;
    for(ll i=0;i<N;i++){
        ll wake = h_prev /2;
        ll need = t > wake ? t - wake : 0;
        // Assign chocolates to current day until sum >= need
        if(H[i] >= need){
            assign_day[i] = day;
            h_prev = wake + H[i];
            day++;
        }
        else{
            ll sum = H[i];
            assign_day[i] = day;
            while(sum < need && i+1 < N){
                i++;
                sum += H[i];
                assign_day[i] = day;
            }
            h_prev = wake + sum;
            day++;
        }
    }
    // If days used less than D, assign remaining chocolates to last day
    while(day <= D){
        day++;
    }
    printf("%lld\n", best);
    for(ll i=0;i<N;i++){
        printf("%lld\n", assign_day[i]);
    }
}