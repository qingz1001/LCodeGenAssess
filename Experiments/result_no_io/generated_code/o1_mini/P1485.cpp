#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef long long ll;

ll m[500005];
ll n, k;

// Function to compute the number of bullets needed for a given p
ll compute_bullets(ll p) {
    ll s = (p > 0) ? (ll)floor(sqrt((double)(p - 1))) : 0;
    // Allocate and initialize difference arrays
    static ll diff_aj2_local[500005];
    static ll diff_bj_local[500005];
    static ll diff_c_local[500005];
    memset(diff_aj2_local, 0, sizeof(ll)*(n+2));
    memset(diff_bj_local, 0, sizeof(ll)*(n+2));
    memset(diff_c_local, 0, sizeof(ll)*(n+2));
    
    ll total_bullets = 0;
    ll a = 0, b = 0, c_val = 0;
    ll damage;
    
    for(ll j =1; j <=n; j++) {
        a += diff_aj2_local[j];
        b += diff_bj_local[j];
        c_val += diff_c_local[j];
        damage = c_val + b * j + a * j * j;
        if(damage < m[j]) {
            ll y = j + s;
            if(y > n) y = n;
            ll d = p - (y - j)*(y - j);
            if(d <=0) {
                return k +1; // Impossible to cover
            }
            ll required = m[j] - damage;
            ll c_bullets = required / d;
            if(required % d !=0) c_bullets++;
            total_bullets += c_bullets;
            if(total_bullets > k) return total_bullets;
            // Update difference arrays
            ll l = y - s;
            if(l <1) l =1;
            ll r = y;
            ll a_update = -c_bullets;
            ll b_update = 2 * y * c_bullets;
            ll c_update = (p - (y - j)*(y - j)) * c_bullets;
            diff_aj2_local[l] += a_update;
            diff_aj2_local[r +1] -= a_update;
            diff_bj_local[l] += b_update;
            diff_bj_local[r +1] -= b_update;
            diff_c_local[l] += c_update;
            diff_c_local[r +1] -= c_update;
        }
    }
    return total_bullets;
}

int main(){
    scanf("%lld %lld", &n, &k);
    for(ll i=1;i<=n;i++) scanf("%lld", &m[i]);
    ll left =1, right = 2;
    // Find an upper bound for p
    while(compute_bullets(right) >k){
        right *=2;
        if(right > 2e12) break; // Avoid overflow
    }
    // Binary search for the minimal p
    while(left < right){
        ll mid = left + (right - left)/2;
        ll bullets = compute_bullets(mid);
        if(bullets <=k){
            right = mid;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld\n", left);
    return 0;
}