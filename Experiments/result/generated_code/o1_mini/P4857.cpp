#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to compute the sum of floor(mid / a[i])
ll compute_sum(ll mid, ll k, ll *a){
    ll sum = 0;
    for(ll i=0;i<k;i++) {
        sum += mid / a[i];
        if(sum < 0) return sum; // Overflow protection
    }
    return sum;
}

int main(){
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll a[k];
    for(ll i=0;i<k;i++) scanf("%lld", &a[i]);

    // Binary search to find minimal T where sum(floor(T/a_i)) >=n
    ll left=1, right=1;
    // Find an upper bound
    while(compute_sum(right, k, a) < n) right *=2;
    ll T=right;
    while(left <= right){
        ll mid = left + (right - left)/2;
        ll s = compute_sum(mid, k, a);
        if(s >=n){
            T = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }

    // Compute S_prev = sum(floor((T-1)/a_i))
    ll S_prev =0;
    for(ll i=0;i<k;i++) S_prev += (T-1)/a[i];

    // Compute n' =n - S_prev
    ll n_prime = n - S_prev;

    // Collect machines where a_i divides T
    ll indices[k];
    ll m =0;
    for(ll i=0;i<k;i++) {
        if(T % a[i] ==0){
            indices[m++] = i;
        }
    }

    // Sort the first m indices by their order (already sorted by index)
    // Assign the first n' machines to have last_command = S_prev + order
    ll last_command[k];
    for(ll i=0;i<k;i++) last_command[i] = (T / a[i]);

    for(ll i=0;i<m && i<n_prime;i++) {
        ll idx = indices[i];
        last_command[idx] = S_prev + i +1;
    }

    // Print the results
    for(ll i=0;i<k;i++) printf("%lld%c", last_command[i], (i==k-1)?'\n':' ');
    return 0;
}